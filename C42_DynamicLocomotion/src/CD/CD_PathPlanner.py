#!/usr/bin/env python

from collections import deque
from Abstractions.PathPlanner import *
import math

###################################################################################
# File created by David Dovrat, 2013.
# For Robil, under project Robil's license of choice
# The code in this file is provided "as is" and comes with no warranty whatsoever
###################################################################################

###################################################################################
#---------------------------------- Waypoint --------------------------------------
###################################################################################

class Waypoint(object):
    """
        The Waypoint class is the basic building block of paths
    """   
    def __init__(self,CoordinateX = 0.0,CoordinateY = 0.0):
        self._fX = CoordinateX
        self._fY = CoordinateY
        
    def GetX(self):
        return self._fX
    
    def SetX(self,X):
        self._fX = X
  
    def GetY(self):
        return self._fY
    
    def SetY(self,Y):
        self._fY = Y      
        
    def GetDistanceFrom(self,otherWaypoint):
        dX = otherWaypoint._fX - self._fX
        dY = otherWaypoint._fY - self._fY
        return math.sqrt(dX*dX+dY*dY)

    def AddWapoint(self,otherWaypoint):
        res = Waypoint()
        res._fX = self._fX + otherWaypoint._fX
        res._fY = self._fY + otherWaypoint._fY
        return res

    def SubWapoint(self,otherWaypoint):
        res = Waypoint()
        res._fX = self._fX - otherWaypoint._fX
        res._fY = self._fY - otherWaypoint._fY
        return res

    def PrintWaypoint(self):
        strWaypoint = " (x=" + str(self._fX) + ", y=" + str(self._fY) + ")"
        return strWaypoint
        
###################################################################################
#---------------------------------- Segment --------------------------------------
###################################################################################
       
class Segment(object):
    """
        The Segment class represents a part in a path between two waypoints: Source to Target
    """  
    def __init__(self,waypointSource,waypointTarget):
        self._Source = Waypoint(waypointSource.GetX(),waypointSource.GetY())
        self._Target = Waypoint(waypointTarget.GetX(),waypointTarget.GetY())
        
    def SetSource(self,waypointSource):
        self._Source._fX = waypointSource._fX
        self._Source._fY = waypointSource._fY
    
    def SetTarget(self,waypointTarget):
        self._Target._fX = waypointTarget._fX
        self._Target._fY = waypointTarget._fY
        
    def GetSource(self):
        return self._Source
    
    def GetTarget(self):
        return self._Target
        
    def GetDistanceFrom(self,waypoint):
        """
            Returns the distance between the segment and the input waypoint in the following format:
            x,y = GetDistanceFrom(waypoint)
                where x is the distance in the u vector direction:
                    x<0 means that waypoint is |x| distance from the segment's source in the direction of -u
                    x=0 means that the waypoint is between the segment's source and target
                    x>0 means that the waypoint is |x| distance away from the segment's target, in the direction of u
                y is the lateral distance from the segment:
                    y<0 means that the waypoint is to the right of the segment
                    y=0 means that the waypoint is on the segment
                    y>0 means that the waypoint is to the left of the segment
        """
        u = [self._Target.GetX() - self._Source.GetX(),self._Target.GetY() - self._Source.GetY()]
        v = [waypoint.GetX() - self._Source.GetX(),waypoint.GetY() - self._Source.GetY()]
        
        _u_ = math.sqrt(u[0]**2+u[1]**2)

        # a X b = |a|*|b|*sin(alpha) => |b|*sin(alpha) = a X b /|a|
        # a dot b = |a|*|b|*cos(alpha) => |b|*cos(alpha) = a dot b /|a|

        if (_u_>0):
            y = (u[0]*v[1]-u[1]*v[0])/_u_
            x = (u[0]*v[0]+u[1]*v[1])/_u_
            if(x>_u_):
                # distance from target
                x = x-_u_
            elif (x>0):
                # between target and source
                x = 0.0
        else:
            y = 0.0
            x = 0.0

        #rospy.loginfo('GetDistanceFromSegment: _u_ = %f sagital = %f; lateral = %f' %(_u_,x,y) )
        #rospy.loginfo('GetDistanceFromSegment: Source(x,y) = (%f,%f) Target(x,y) = (%f,%f)' %(self._Source.GetX(),self._Source.GetY(),self._Target.GetX(),self._Target.GetY()) )

        return x,y
    
    def GetYaw(self):
        """
            Returns the yaw in radians - in Front Left Up Coordinates, with the origin set at system init
        """
        u = [self._Target.GetX() - self._Source.GetX(),self._Target.GetY() - self._Source.GetY()]
        _u_ = math.sqrt(u[0]**2+u[1]**2)
        if (_u_>0):
            u = [u[0]/_u_, u[1]/_u_]
        else:
            u = [1,0]

        #rospy.loginfo('GetYaw: u_norm = %f; u_x = %f, u_y = %f' %(_u_,u[0],u[1] ) )
        
        return math.atan2(u[1],u[0])

###################################################################################
#--------------------------- Local Path Planner -----------------------------------
###################################################################################

class CD_PathPlanner(PathPlanner):
    """
        The LocalPathPlanner class plans the next few steps for the ZMP module
    """
    
    def __init__(self):
        self._Path = deque([])
        self._Position = Waypoint()
        self._CurrentSegment = Segment(self._Position,self._Position)
        self._PathReady = False
        self._EndOfPath = False
        self._EndOfSegment = False
  
    def SetPath(self,waypointList):
        self._Path = deque(waypointList)
        if (len(self._Path)<2):
            if(len(self._Path)<1):
                self._CurrentSegment.SetSource(self._Position)
                self._CurrentSegment.SetTarget(self._Position)
            else:
                self._CurrentSegment.SetSource(self._Position)
                self._CurrentSegment.SetTarget(self._Path.popleft())
        else:
            self._CurrentSegment.SetSource(self._Path.popleft())
            self._CurrentSegment.SetTarget(self._Path.popleft()) 
        self._PathReady = True
        self._EndOfPath = False
        self._EndOfSegment = False   
        
    def GetPath(self):
        return self._Path
        
    def GetPathError(self):
        sagital,lateral = self._CurrentSegment.GetDistanceFrom(self._Position)
        return lateral
        
    def GetPos(self):
		return self._Position
    
    def GetTargetYaw(self):
        return self._CurrentSegment.GetYaw()

    def GetAngleToNextSegment(self):
        NextSegment = Segment(self._CurrentSegment.GetTarget(),self._Path[0])
        return NextSegment.GetYaw()-self._CurrentSegment.GetYaw()
    
    def GetCloseEnoughToTargetDistance(self):
        return 0.4
 
    def UpdatePosition(self,CoordinateX,CoordinateY,Preview_Distance=0.0):
        """
            Updates the position, returns true if at end of current path, false otherwise
        """
        self._Position.SetX(CoordinateX)
        self._Position.SetY(CoordinateY)
        if self.IsActive():
            sagital,lateral = self._CurrentSegment.GetDistanceFrom(self._Position)
            distanceFromTarget = self._CurrentSegment.GetTarget().GetDistanceFrom(self._Position)
            #rospy.loginfo('UpdatePosition: distanceFromTarget = %f' %(distanceFromTarget))
            if ((sagital>0.0)or(distanceFromTarget < (self.GetCloseEnoughToTargetDistance()+Preview_Distance) )):
                #rospy.loginfo('UpdatePosition: distanceFromTarget = %f' %(distanceFromTarget))
                self._EndOfSegment = True
                if(len(self._Path)==0):
                    self._EndOfPath = True
        
    def PromoteSegment(self):
        if (0<len(self._Path)):
            self._CurrentSegment.SetSource(self._CurrentSegment.GetTarget())
            self._CurrentSegment.SetTarget(self._Path.popleft())
            self._EndOfSegment = False
    
    def Stop(self):
        self._PathReady = False 

    def IsActive(self):
        return self._PathReady
    
    def IsEndOfSegment(self):
        return self._EndOfSegment
    
    def IsEndOfPath(self):
        return self._EndOfPath

    def GetTargetDistance(self):
        return self._CurrentSegment.GetTarget().GetDistanceFrom(self._Position) - self.GetCloseEnoughToTargetDistance()


###################################################################################
# a little testing script
###################################################################################

if __name__ == "__main__":
    pass



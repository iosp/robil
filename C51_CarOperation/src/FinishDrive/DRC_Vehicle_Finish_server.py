#!/usr/bin/env python
import roslib; roslib.load_manifest('C51_CarOperation')
import rospy
import actionlib
import C51_CarOperation.msg
from geometry_msgs.msg import Twist
import geometry_msgs.msg
from nav_msgs.msg import Odometry
from std_msgs.msg import  Float64
from geometry_msgs.msg import Pose
from directionClient import Switch_client
from HBClient import HB_client

class FinishDrive(object):
    _feedback = C51_CarOperation.msg.DriveFeedback()
    _result   = C51_CarOperation.msg.DriveResult()
    
    def __init__(self, name):    
        self._action_name = name
        self._as = actionlib.SimpleActionServer(self._action_name, C51_CarOperation.msg.DriveAction, execute_cb=self.FinishDriveCallback, auto_start=False)
        self._as.start()
    
    def FinishDriveCallback(self, goal):
        # helper variables
        success = True
        if self._as.is_preempt_requested():
            rospy.loginfo('%s: Preempted' % self._action_name)
            self._as.set_preempted()
            success = False
            
        if success:
            #DRC Vehicles controllers online - should be replaced with C67 module
            Switch_client(2)
            HB_client(2)         #handbrake online
            gasP=Gas() #gas pedal online
            brakeP=Brake() #gas pedal online
            Steer=SW()      #steering wheel online
            # - release on brake - and pull handbrake
            brakeP.brake(0)
            self._feedback.complete = 100
            self._result.success = 0
            self._result.description = "Finished"
            self._result.plan = "Finished"
            
            self._as.publish_feedback(self._feedback)
        if success:
            rospy.loginfo('Car is now parked - hand brake is pulled and brake pedal is released!')
            self._as.set_succeeded(self._result)
        #----------------hand brake released --------------------------#




class Gas:
    status=-11
    pub=0
    sub=0
    def __init__(self):
        self.pub = rospy.Publisher('drc_vehicle/gas_pedal/cmd', Float64)
        self.sub = rospy.Subscriber('/drc_vehicle/gas_pedal/state', Float64, self.gasCallback)
    def gasCallback(self, data):
        self.status=data.data

    def gas(self, num):
        self.pub.publish(num)

class Brake:
    status=-11
    pub=0
    sub=0
    def __init__(self):
        self.pub = rospy.Publisher('drc_vehicle/brake_pedal/cmd', Float64)
        self.sub = rospy.Subscriber('/drc_vehicle/brake_pedal/state', Float64, self.brakeCallback)
    def brakeCallback(self, data):
        self.status=data.data

    def brake(self, num):
        self.pub.publish(num)

class SW:
    status=0
    pub=0
    sub=0
    def __init__(self):
        self.pub = rospy.Publisher('drc_vehicle/hand_wheel/cmd', Float64)
        self.sub = rospy.Subscriber('/drc_vehicle/hand_wheel/state', Float64, self.SWCallback)
    def SWCallback(self, data):
        self.status=data.data

    def turn(self, num):
        self.pub.publish(num)

if __name__ == '__main__':
    try:
        rospy.init_node('FinishDrive')
        FinishDrive(rospy.get_name())   
        rospy.spin()
    except rospy.ROSInterruptException: 
        print "Did not initialized vehicle"



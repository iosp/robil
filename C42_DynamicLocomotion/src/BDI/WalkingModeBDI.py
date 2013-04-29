#!/usr/bin/env python
import roslib
roslib.load_manifest('C42_DynamicLocomotion')
from Abstractions.WalkingMode import *
import time
from atlas_msgs.msg import AtlasCommand, AtlasSimInterfaceCommand, AtlasSimInterfaceState, AtlasState, AtlasBehaviorStepData
from sensor_msgs.msg import Imu
import PyKDL
from tf_conversions import posemath
from atlas_msgs.msg import AtlasSimInterfaceCommand, AtlasSimInterfaceState, AtlasState
from geometry_msgs.msg import Pose, Point
from std_msgs.msg import String
from tf.transformations import quaternion_from_euler, euler_from_quaternion

from BDI_StateMachine import *

import math
import rospy
import sys

###################################################################################
# File created by David Dovrat, 2013.
# For Robil, under project Robil's license of choice
# The code in this file is provided "as is" and comes with no warranty whatsoever
###################################################################################

class WalkingModeBDI(WalkingMode):

    def __init__(self,localPathPlanner):
        # Initialize atlas mode and atlas_sim_interface_command publishers        
        self.mode = rospy.Publisher('/atlas/mode', String, None, False, True, None)
        self.asi_command = rospy.Publisher('/atlas/atlas_sim_interface_command', AtlasSimInterfaceCommand, None, False, True, None)
        self._StateMachine = BDI_StateMachine()
        self._LPP = localPathPlanner
        self._yaw = 0.0
                
    def Initialize(self):
        # Puts robot into freeze behavior, all joints controlled
        # Put the robot into a known state
        k_effort = [0] * 28
        freeze = AtlasSimInterfaceCommand(None,AtlasSimInterfaceCommand.FREEZE, None, None, None, None, k_effort )
        self.asi_command.publish(freeze)
        
        # Puts robot into stand_prep behavior, a joint configuration suitable
        # to go into stand mode
        stand_prep = AtlasSimInterfaceCommand(None,AtlasSimInterfaceCommand.STAND_PREP, None, None, None, None, k_effort)
        self.asi_command.publish(stand_prep)

        rospy.sleep(2.0)
        self.mode.publish("nominal")
        
        # Put robot into stand position
        stand = AtlasSimInterfaceCommand(None,AtlasSimInterfaceCommand.STAND, None, None, None, None, k_effort)
                
        rospy.sleep(0.3)
        
        self.asi_command.publish(stand)
        
        # Initialize some variables before starting.
        self.step_index = 0
        self.is_swaying = False
    
    def StartWalking(self):
        return 0.3
    
    def Walk(self):
        # Subscribe to atlas_state and atlas_sim_interface_state topics.
        self.asi_state = rospy.Subscriber('/atlas/atlas_sim_interface_state', AtlasSimInterfaceState, self.asi_state_cb)
        self.atlas_state = rospy.Subscriber('/atlas/atlas_state', AtlasState, self.atlas_state_cb)

        self._StateMachine.GoForward()

        while not rospy.is_shutdown():
            rospy.spin()
    
    def Stop(self):
        pass
    
    def EmergencyStop(self):
        pass    

###################################################################################
#--------------------------- CallBacks --------------------------------------------
###################################################################################

    # /atlas/atlas_sim_interface_state callback. Before publishing a walk command, we need
    # the current robot position   
    def asi_state_cb(self, state):
        if (self._LPP.IsActive()):
            try:
                x = self.robot_position.x
            except AttributeError:            
                self.robot_position = Point()
                self.robot_position.x = state.pos_est.position.x
                self.robot_position.y = state.pos_est.position.y
                self.robot_position.z = state.pos_est.position.z  
            
            targetYaw = self._LPP.GetTargetYaw()
            delatYaw = targetYaw - self._yaw
            sinYaw = math.sin(delatYaw)

            self._LPP.UpdatePosition(self.robot_position.x,self.robot_position.y)
            # print(sinYaw)
            # if (sinYaw > 0.5):
            #     self._StateMachine.TurnLeft()
            #     print("Left")
            # elif (sinYaw < -0.5):
            #     self._StateMachine.TurnRight()
            #     print("Right")
            # elif (math.fabs(sinYaw) < 0.1):
            #     self._StateMachine.GoForward()

            command = self._StateMachine.Step(self.robot_position,state.behavior_feedback.walk_feedback.next_step_index_needed)
            self.asi_command.publish(command)
 
    # /atlas/atlas_state callback. This message provides the orientation of the robot from the torso IMU
    # This will be important if you need to transform your step commands from the robot's local frame to world frame
    def atlas_state_cb(self, state):
        # If you don't reset to harnessed, then you need to get the current orientation
        roll, pitch, yaw = euler_from_quaternion([state.orientation.x, state.orientation.y, state.orientation.z, state.orientation.w])
        self._yaw = yaw
        return True

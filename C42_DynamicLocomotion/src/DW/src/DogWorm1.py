#! /usr/bin/env python
import roslib; roslib.load_manifest('DogWorm')
import math, rospy, os, rosparam
from sensor_msgs.msg import JointState
from nav_msgs.msg import Odometry
from numpy import zeros, array, linspace, arange
import numpy as np
from JointController import JointCommands_msg_handler
from JointController import hand_joint_controller
from robot_state import robot_state
from atlas_msgs.msg import AtlasState
from math import ceil
import yaml
from copy import copy
from std_srvs.srv import Empty

class DW_Controller(object):
    """DW_Controller"""
    def __init__(self, arg):
        super(DW_Controller, self).__init__()

        ##################################################################
        ######################## GAIT PARAMETERS #########################
        ##################################################################
        
        ##################################################################
        ###################### Basic Standing Pose #######################
        ##################################################################

        self.BasStndPose = zeros(28)
        self.BasStndPose[17] = -1.3
        self.BasStndPose[17+6] = 1.3 
        self.BasStndPose[18] = self.BasStndPose[18+6] = 1.5
        #         # Pose[18] -= 1.5
        #         # Pose[20] += 3.1
        # # self.BasStndPose[18] = self.BasStndPose[18+6] = 0
        # self.BasStndPose[20] = self.BasStndPose[20+6] = 1.5
        self.BasStndPose[21] = 0.4
        self.BasStndPose[27] = -0.4

        self.BaseHandPose = zeros(12)
        self.BaseHandPose[1] = self.BaseHandPose[1+3] = self.BaseHandPose[1+6] = 1.5


        ##################################################################
        ####################### Sit Down Sequence ########################
        ##################################################################

        self.SitDwnSeq1 = copy(self.BasStndPose)
        self.SitDwnSeq1[1] = 0.5
        self.SitDwnSeq1[6] = self.SitDwnSeq1[6+6] = -1.5
        self.SitDwnSeq1[7] = self.SitDwnSeq1[7+6] = 2.4
        self.SitDwnSeq1[8] = self.SitDwnSeq1[8+6] = -1.2
        self.SitDwnSeq1[16] = self.SitDwnSeq1[16+6] = 1.05
        self.SitDwnSeq1[17] = -1.25
        self.SitDwnSeq1[17+6] = 1.25
        self.SitDwnSeq1[18] = self.SitDwnSeq1[18+6] = 2.2
        self.SitDwnSeq1[21] = 1.4
        self.SitDwnSeq1[21+6] = -1.4

        self.SitDwnSeq2 = copy(self.SitDwnSeq1)
        self.SitDwnSeq2[1] = 1.2
        self.SitDwnSeq2[5] = 0.1
        self.SitDwnSeq2[5+6] = -0.1
        self.SitDwnSeq2[6] = self.SitDwnSeq2[6+6] = -1.5
        self.SitDwnSeq2[7] = self.SitDwnSeq2[7+6] = 0.9
        self.SitDwnSeq2[8] = self.SitDwnSeq2[8+6] = 1.3
        self.SitDwnSeq2[16] = self.SitDwnSeq2[16+6] = -1
        self.SitDwnSeq2[17] = -0.8
        self.SitDwnSeq2[17+6] = 0.8
        self.SitDwnSeq2[18] = self.SitDwnSeq2[18+6] = 1.2
        self.SitDwnSeq2[19] = 0.9
        self.SitDwnSeq2[19+6] = -0.9
        self.SitDwnSeq2[21] = 0
        self.SitDwnSeq2[21+6] = -0


        self.ArmSeq1 = copy(self.SitDwnSeq2)
        self.ArmSeq1[16] = self.ArmSeq1[16+6] = 1.3
        self.ArmSeq1[17] = -0.9
        self.ArmSeq1[17+6] = 0.9
        self.ArmSeq1[18] = self.ArmSeq1[18+6] = 1.2
        self.ArmSeq1[19] = 2.2
        self.ArmSeq1[19+6] = -2.2
        self.ArmSeq1[21] = 1.
        self.ArmSeq1[21+6] = -1.

        self.ArmSeq2 = copy(self.SitDwnSeq2)
        self.ArmSeq2[16] = self.ArmSeq2[16+6] = 1.3
        self.ArmSeq2[17] = -1.7
        self.ArmSeq2[17+6] = 1.7
        self.ArmSeq2[18] = self.ArmSeq2[18+6] = 2.2
        self.ArmSeq2[19] = 0.5
        self.ArmSeq2[19+6] = -0.5
        self.ArmSeq2[21] = -0.5
        self.ArmSeq2[21+6] = 0.5

        self.ArmSeq3 = copy(self.SitDwnSeq2)
        self.ArmSeq3[16] = self.ArmSeq3[16+6] = -1
        self.ArmSeq3[17] = -1.0
        self.ArmSeq3[17+6] = 1.0
        self.ArmSeq3[18] = self.ArmSeq3[18+6] = 1.2
        self.ArmSeq3[19] = 0.5
        self.ArmSeq3[19+6] = -0.5
        self.ArmSeq3[21] = 0
        self.ArmSeq3[21+6] = -0

        ##################################################################
        ########################## Hip motions ###########################
        ##################################################################

        self.HipFwd = copy(self.SitDwnSeq1)
        self.HipFwd[1] = 0.2
        self.HipFwd[6] = self.HipFwd[6+6] = -1.0
        self.HipFwd[7] = self.HipFwd[7+6] = 2.45
        self.HipFwd[8] = self.HipFwd[8+6] = -0.4
        self.HipFwd[16] = self.HipFwd[16+6] = 1.4
        self.HipFwd[17] = -0.8
        self.HipFwd[17+6] = 0.8

        self.HipBack = copy(self.SitDwnSeq1)
        self.HipBack[1] = 0.6
        self.HipBack[6] = self.HipBack[6+6] = -1.4
        self.HipBack[7] = self.HipBack[7+6] = 2.0
        self.HipBack[8] = self.HipBack[8+6] = 0.4
        self.HipBack[16] = self.HipBack[16+6] = 0.8
        self.HipBack[17] = -1.4
        self.HipBack[17+6] = 1.4


        ##################################################################
        ########################## Arm motions ###########################
        ##################################################################

        self.R_arm_lift = copy(self.HipFwd)
        # self.R_arm_lift[]
        ##################################################################
        ########################## INITIALIZE ############################
        ##################################################################

        self._robot_name = "atlas"
        self._jnt_names = ['back_lbz', 'back_mby', 'back_ubx', 'neck_ay', #3
                           'l_leg_uhz', 'l_leg_mhx', 'l_leg_lhy', 'l_leg_kny', 'l_leg_uay', 'l_leg_lax', #9
                           'r_leg_uhz', 'r_leg_mhx', 'r_leg_lhy', 'r_leg_kny', 'r_leg_uay', 'r_leg_lax', #15
                           'l_arm_usy', 'l_arm_shx', 'l_arm_ely', 'l_arm_elx', 'l_arm_uwy', 'l_arm_mwx', #21
                           'r_arm_usy', 'r_arm_shx', 'r_arm_ely', 'r_arm_elx', 'r_arm_uwy', 'r_arm_mwx'] #27

        self.LegL1 = math.sqrt(0.045**2+0.375**2)
        self.LegL2 = 0.422
        self.ArmL1 = math.sqrt(0.013**2+0.306**2)
        self.ArmL2 = math.sqrt(0.013**2+0.246**2)

        self.HandHeight0 = 0.27
        self.LegHeight0 = 0.0836

        self.ArmAngle0 = math.atan2(0.22,0.38)

        # Initialize joint commands handler
        self.JC = JointCommands_msg_handler(self._robot_name,self._jnt_names)
        self.LHC = hand_joint_controller("left")
        self.RHC = hand_joint_controller("right")

        # Initialize robot state listener
        self.RS = robot_state(self._jnt_names)
        self.MsgSub = rospy.Subscriber('/'+self._robot_name+'/atlas_state',AtlasState,self.RS_cb)
        self.OdomSub = rospy.Subscriber('/ground_truth_odom',Odometry,self.Odom_cb)
        self.GlobalPos = 0

        self.reset_srv = rospy.ServiceProxy('/gazebo/reset_models', Empty)

        ##################################################################
        ######################## Controller Gains ########################
        ##################################################################

        self.JC.set_gains('l_leg_uhz',1000,0,10)
        self.JC.set_gains('r_leg_uhz',1000,0,10)
        self.JC.set_gains('l_leg_mhx',1000,0,10)
        self.JC.set_gains('r_leg_mhx',1000,0,10)
        self.JC.set_gains('back_lbz',5000,0,10)
        self.JC.set_gains('back_ubx',1000,0,10)
        self.JC.set_gains('l_arm_usy',1000,0,10)
        self.JC.set_gains('r_arm_usy',1000,0,10)
        self.JC.set_gains('l_arm_shx',1000,0,10)
        self.JC.set_gains('r_arm_shx',1000,0,10)
        self.JC.set_gains('l_arm_ely',1000,0,10)
        self.JC.set_gains('r_arm_ely',1000,0,10)
        self.JC.set_gains("l_arm_elx",1200,0,5)
        self.JC.set_gains("r_arm_elx",1200,0,5)
        self.JC.send_command()

    ##################################################################
    ########################### FUNCTIONS ############################
    ##################################################################

    def SeqWithBalance(self,pos1,pos2,T,dt):
        if len(pos1) == len(pos2) == len(self._jnt_names):
            N = ceil(T/dt)
            pos1 = array(pos1)
            pos2 = array(pos2)
            COM_pos0x = self.GlobalPos.x
            COM_pos0y = self.GlobalPos.y
            back_mby_pos = 0

            for ratio in linspace(0, 1, N):
              interpCommand = (1-ratio)*pos1 + ratio * pos2

              # Balance torso
              back_mby_pos = interpCommand[1]-3*(self.GlobalPos.x - COM_pos0x)
              back_ubx_pos = interpCommand[2]+2*(self.GlobalPos.y - COM_pos0y)

              self.JC.set_all_pos([ float(x) for x in interpCommand ])
              self.JC.set_pos("back_mby",back_mby_pos)
              self.JC.set_pos("back_ubx",back_ubx_pos)

              self.JC.send_command()
              rospy.sleep(dt)
        else:
            print 'position command legth doest fit'

    def Sit(self,T):
        self.JC.set_gains("l_arm_elx",5,0,20)
        self.JC.set_gains("r_arm_elx",5,0,20)
        self.SeqWithBalance(self.RS.GetJointPos(),self.SitDwnSeq1,T*0.3,0.005)
        self.JC.set_pos("l_leg_uay",-0.1)
        self.JC.set_pos("r_leg_uay",-0.1)
        self.JC.set_gains("l_leg_uay",10,0,5)
        self.JC.set_gains("r_leg_uay",10,0,5)
        self.JC.set_gains("l_leg_lax",10,0,5)
        self.JC.set_gains("r_leg_lax",10,0,5)
        self.JC.send_command()
        rospy.sleep(T*0.2)
        self.JC.set_gains("l_arm_elx",1200,0,5)
        self.JC.set_gains("r_arm_elx",1200,0,5)
        self.JC.set_gains("l_leg_uay",50,0,5)
        self.JC.set_gains("r_leg_uay",50,0,5)
        self.JC.set_gains("l_leg_lax",50,0,5)
        self.JC.set_gains("r_leg_lax",50,0,5)
        self.JC.send_command()
        rospy.sleep(T*0.4)
        # self.JC.send_pos_traj(self.RS.GetJointPos(),self.SitDwnSeq2,T*0.2,0.005)

    def MoveHip(self,dir_x,dir_y):
        if dir_y == "left":
            if dir_x == "fwd":
                Pose = copy(self.HipFwd)
                Pose[5] -= 0.4
                Pose[5+6] -= 0.4
                # Pose[16] += 0.2
                Pose[16+6] -= 0.2
                Pose[17] -= 0.1
                Pose[17+6] += 0.1 
            if dir_x == "back":
                Pose = copy(self.HipBack)
                # Pose[2] += 0.3
                Pose[4+6] -= 0.6
                Pose[5] -= 0.4
                Pose[5+6] -= 0.4
                Pose[6+6] -= 0.2
                Pose[7+6] += 0.2
                Pose[16] += 0.4
                Pose[16+6] -= 0.2
                Pose[17] -= 0.1
                Pose[17+6] += 0.2 

        if dir_y == "right":
            if dir_x == "fwd":
                Pose = copy(self.HipFwd)
                Pose[5] += 0.4
                Pose[5+6] += 0.4
                # Pose[16] -= 0.2
                Pose[16+6] += 0.2
                Pose[17] -= 0.1
                Pose[17+6] += 0.1 
            if dir_x == "back":
                Pose = copy(self.HipBack)
                # Pose[2] -= 0.3
                Pose[4] += 0.3
                Pose[5] += 0.4
                Pose[5+6] += 0.4
                Pose[16] -= 0.1
                Pose[16+6] += 0.4
                Pose[17] += 0.4
                Pose[17+6] += 0.2

        self.JC.send_pos_traj(self.RS.GetJointPos(),Pose,1,0.01) 
        return Pose

    def RaiseHand(self,which,start_pose):
        if which == "right":
            Pose = copy(start_pose)
            Pose[0] += 0.3
            Pose[19+6] -= 1.4
        if which == "left":
            Pose = copy(start_pose)
            Pose[0] -= 0.3
            Pose[19] += 1.4

        self.JC.send_pos_traj(self.RS.GetJointPos(),Pose,1,0.01) 
        return Pose

    def MoveHand(self,which,start_pose):
        if which == "right":
            Pose = copy(start_pose)
            Pose[16+6] += 0.2
            Pose[17+6] += 0.4
            Pose[19+6] += 1.4
            self.JC.send_pos_traj(self.RS.GetJointPos(),Pose,0.5,0.01)         
            Pose[0] -= 0.3
        if which == "left":
            Pose = copy(start_pose)
            Pose[16] += 0.2
            Pose[17] -= 0.4
            Pose[19] -= 1.4
            self.JC.send_pos_traj(self.RS.GetJointPos(),Pose,0.5,0.01)         
            Pose[0] += 0.3

        self.JC.send_pos_traj(self.RS.GetJointPos(),Pose,0.5,0.01)    
        return Pose

    def IK_Leg(self,side,x,y,z,init_pose):
        pose = copy(init_pose)
        if side=="left":
            L = math.sqrt(x**2+y**2+z**2)
            theta_mhx = math.atan2(y,x) + pose[2]
            theta_lhy = math.atan2(z,math.sqrt(x**2+y**2))-math.acos((self.LegL1**2+L**2-self.LegL2**2)/(2*self.LegL1*L))
            theta_kny = math.pi-math.acos((self.LegL1**2+self.LegL2**2-L**2)/(2*self.LegL1*self.LegL2))
            side_id = 0

        if side=="right":
            L = math.sqrt(x**2+y**2+z**2)
            theta_mhx = -math.atan2(y,x) + pose[2]
            theta_lhy = math.atan2(z,math.sqrt(x**2+y**2))-math.acos((self.LegL1**2+L**2-self.LegL2**2)/(2*self.LegL1*L))
            theta_kny = math.pi-math.acos((self.LegL1**2+self.LegL2**2-L**2)/(2*self.LegL1*self.LegL2))
            side_id = 6

        pose[5+side_id] = theta_mhx
        pose[6+side_id] = theta_lhy
        pose[7+side_id] = theta_kny
        # Ankle orientation compensation
        pose[8+side_id] = math.pi/2 - (theta_lhy + theta_kny)
        return pose

    def IK_Arm(self,side,x,y,z,init_pose):
        pose = copy(init_pose)
        alpha_max = 0.39
        alpha_min = -1 #arbitrary
        beta_max = 1.2 #arbitrary
        beta_min = -0.34 # (-0.7? joint limit)
        x2=x*math.cos(self.ArmAngle0)+y*math.sin(self.ArmAngle0)
        y2=-x*math.sin(self.ArmAngle0)+y*math.cos(self.ArmAngle0)

        L = math.sqrt(x2**2+y2**2+z**2)
        alpha = math.atan2(y2,-z)

        if alpha>alpha_max:
            alpha -= math.pi
            if alpha<alpha_min:
                print "Error, position can't be reached with joint usy"
                alpha = alpha_min

        if alpha<alpha_min:
            alpha += math.pi
            if alpha>alpha_max:
                print "Error, position can't be reached with joint usy"
                alpha = alpha_max

        beta1 = math.acos((L**2+self.ArmL1**2-self.ArmL2**2)/(2*L*self.ArmL1))
        if z<=0:
            beta2 = math.atan2(math.sqrt(y2**2+z**2),x2)
        else:
            beta2 = -math.atan2(math.sqrt(y2**2+z**2),x2)

        beta = beta1-beta2
        if beta>beta_max:
            print "Error, position can't be reached with joint shx"
        if beta<beta_min:
            print "Error, position can't be reached with joint shx"

        gamma = math.acos((self.ArmL1**2+self.ArmL2**2-L**2)/(2*self.ArmL1*self.ArmL2))

        # Wrist orientation compensation
        theta = math.atan(math.sin(alpha)/(math.cos(alpha)*math.sin(beta+gamma-math.pi/2)))
        # phi = math.atan(-(math.cos(alpha)*math.sin(beta+gamma-math.pi/2))/(math.sin(theta)*math.cos(alpha)*math.sin(beta+gamma-math.pi/2)+math.sin(alpha)*math.cos(theta)))
        # phi = math.pi/2+math.atan2(math.sin(alpha)*math.cos(beta+gamma-math.pi/2),-math.sin(beta+gamma-math.pi/2))
        phi = 0.1*math.pi-math.acos(math.cos(alpha)*math.cos(beta+gamma-math.pi/2))

        if side=="right":
            theta_usy = -math.pi/2 - alpha
            theta_shx = self.ArmAngle0 - math.pi/2 + beta
            theta_elx = -1*(math.pi - gamma)
            side_id = 6
        if side=="left":
            theta_usy = -math.pi/2 - alpha
            theta_shx = -1*(self.ArmAngle0 - math.pi/2 + beta)
            theta_elx = math.pi - gamma
            phi = -phi
            side_id = 0

        math.pi/2
        pose[16+side_id] = theta_usy
        pose[17+side_id] = theta_shx
        pose[19+side_id] = theta_elx
        # Wrist orientation compensation
        pose[20+side_id] = theta
        pose[21+side_id] = phi
        return pose


    def ResetPose(self):
        self.JC.set_all_pos([0]*28)
        self.JC.send_command()

    def RS_cb(self,msg):
        self.RS.UpdateState(msg)

    def Odom_cb(self,msg):
        self.GlobalPos = msg.pose.pose.position

    def reset(self):
        self.reset_srv()
        rospy.sleep(1)

        while self.GlobalPos.z<0.9 or self.GlobalPos.z>0.94 or abs(self.GlobalPos.x)>0.5:
            self.reset_srv()
            rospy.sleep(1)

    def Run(self,TimeOut = 0):
        rospy.sleep(0.1)

        self.JC.reset_command()
        self.JC.reset_gains()
        self.JC.send_pos_traj(self.RS.GetJointPos(),self.BasStndPose,0.5,0.01) 
        self.LHC.set_all_pos(self.BaseHandPose)
        self.RHC.set_all_pos(self.BaseHandPose)
        self.LHC.send_command()
        self.RHC.send_command()

        self.reset()
        rospy.sleep(1)

        self.Sit(2)
        rospy.sleep(0.5)

        for x in range(10):
            pos1 = copy(self.SitDwnSeq1)
            pos1[1] = 0.9
            pos1[8] = pos1[8+6] = -0.1
            pos1[6] = pos1[6+6] = -1.9
            self.JC.send_pos_traj(self.RS.GetJointPos(),pos1,1.,0.01) 

            pos2a = copy(pos1)
            pos2a[7] = pos2a[7+6] = 1.6
            pos2a[8] = pos2a[8+6] = 0.8
            self.JC.send_pos_traj(self.RS.GetJointPos(),pos2a,1.,0.01) 

            pos2b = copy(pos2a)
            pos2b[6] = pos2b[6+6] = -1.2
            self.JC.send_pos_traj(self.RS.GetJointPos(),pos2b,1.,0.01) 

            pos3 = copy(pos2b)
            pos3[6] = pos3[6+6] = -1.6
            pos3[21] = pos3[21+6] = 0
            self.JC.send_pos_traj(self.RS.GetJointPos(),pos3,1.,0.01) 

            pos4 = copy(pos3)
            pos4[16] = pos4[16+6] = 1.5
            pos4[18] = pos4[18+6] = 2.6
            pos4[19] = 2
            pos4[19+6] = -2
            self.JC.send_pos_traj(self.RS.GetJointPos(),pos4,1.,0.01) 

            pos5 = copy(pos4)
            pos5[16] = pos5[16+6] = 1.0
            pos5[17] = -1.1
            pos5[17+6] = 1.1
            pos5[18] = pos5[18+6] = 2.5
            pos5[19] = 1.1
            pos5[19+6] = -1.1
            self.JC.send_pos_traj(self.RS.GetJointPos(),pos5,1.,0.01) 

            pos6 = copy(pos5)
            pos6[16] = pos6[16+6] = 0.3
            pos6[17] = -1.3
            pos6[17+6] = 1.3
            pos6[18] = pos6[18+6] = 2.2
            pos6[19] = 0.3
            pos6[19+6] = -0.3
            self.JC.send_pos_traj(self.RS.GetJointPos(),pos6,1.,0.01) 

            pos7 = copy(pos6)
            pos7[7] = pos7[7+6] = 2.2
            pos7[8] = pos7[8+6] = 0.2
            pos7[16] = pos7[16+6] = 1.0
            pos7[17] = -1.1
            pos7[17+6] = 1.1
            pos7[18] = pos7[18+6] = 2.5
            self.JC.send_pos_traj(self.RS.GetJointPos(),pos7,1.,0.01) 

        # pos1 = copy(self.ArmSeq2)
        # pos1[7] = pos1[7+6] = 2.8
        # pos1[4] = 1.1
        # pos1[4+6] = -1.1
        # self.JC.send_pos_traj(self.RS.GetJointPos(),pos1,1,0.01) 
        # pos2 = copy(self.SitDwnSeq2)
        # T=0.3
        # for x in range(10):
        #     # self.JC.send_pos_traj(self.RS.GetJointPos(),pos1,T,0.01) 
        #     # self.JC.send_pos_traj(self.RS.GetJointPos(),pos2,T,0.01) 
        #     self.JC.send_pos_traj(self.RS.GetJointPos(),self.ArmSeq3,T,0.01) 
        #     self.JC.send_pos_traj(self.RS.GetJointPos(),self.ArmSeq2,T,0.01) 
        #     self.JC.send_pos_traj(self.RS.GetJointPos(),self.ArmSeq1,T,0.01) 

        # self.JC.send_pos_traj(self.RS.GetJointPos(),init_pose,1.,0.01) 

        # pos = copy(self.BasStndPose)
        # delta = 0.03
        # for x in range(10):
        #     pos[5] -=delta
        #     pos[5+6] -=delta
        #     pos[9] +=delta
        #     pos[9+6] +=delta
        #     self.SeqWithBalance(self.RS.GetJointPos(),pos,2,0.005)
        #     pos[5] +=delta
        #     pos[5+6] +=delta
        #     pos[9] -=delta
        #     pos[9+6] -=delta
        #     self.SeqWithBalance(self.RS.GetJointPos(),pos,2,0.005)
        

        


##################################################################
######################### USAGE EXAMPLE ##########################
##################################################################

if __name__=='__main__':
    DW = DW_Controller([])
    DW.Run(60)

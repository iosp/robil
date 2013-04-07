#!/usr/bin/env python

#############################################################################
####                                                                       ##
####    creates the LEG_IK node which computes the IK of the foot in 3D    ##
####    the service handles LegIk.srv sevices                              ##
####    request is foot coordinates (x,y,z) with reference to the hip      ##
####    resposes are hip (mhx,lhy,uhz) and knee (kny) angles               ##
####    use by typing rostopic pub posi leg_ik/mod "pos: {x: 0.01, y: 0.2, ##
####    z: -0.2, r: 0.0, p: 0.0, w: 0.0}                                   ##
####                                                                       ##
####    usage:                                                             ##
####    1) rosrun ZMP zmp_main.py rosrun                                   ##
####    2) rosrun leg_ik leg_ik_server3D.py                                ##
####    3) leg_ik IK_Caller.py                                             ##
####    4) start walking  rostopic pub /zmp_walk_command std_msgs/Int32 1  ##
####    5) stop walking   rostopic pub /zmp_walk_command std_msgs/Int32 0  ##
####                                                                       ##
#############################################################################

import roslib; roslib.load_manifest('C42_Leg_IK')
from drc2_tools import *
# from leg_ik.srv import *
# from leg_ik.msg import *
from std_msgs.msg import Float64
from sensor_msgs.msg import *
from C42_ZMPWalk.msg import walking_trajectory
import rospy, math, sys
from Impedance_Control import Joint_Stiffness_Controller
from pylab import *
from leg_ik_func import swing_leg_ik,stance_leg_ik
from IKException import IKReachException
from geometry_msgs.msg import *
import copy
from Impedance_Control import Position_Stiffness_Controller
class Nasmpace: pass
ns = Nasmpace()
#ns.LegAng = LegIkResponse()

PSC_right_swing_leg = Position_Stiffness_Controller('R_Swing Leg', 50000, True, False) # name, stiffness, triggered_controller, bypass_input2output [True/False]
PSC_left_swing_leg = Position_Stiffness_Controller('L_Swing Leg', 30000, True, False) # name, stiffness, triggered_controller, bypass_input2output [True/False]

# swing_leg_ik = rospy.ServiceProxy('swing_leg_ik', LegIk)
# stance_leg_ik = rospy.ServiceProxy('stance_leg_ik', LegIk)


##########################################################################################
# request from foot contact publisher to update Position Stiffness Controllers avg force #
##########################################################################################

def get_r_foot_contact(msg):
    
    PSC_right_swing_leg.UpdateForce(msg.force.z)
    
    #rospy.loginfo("Stiffness Controllers joint state updated ")  

def get_l_foot_contact(msg):
    
    PSC_left_swing_leg.UpdateForce(msg.force.z) 

#################################################################################
#                     request from IK and publish angles                        #
#################################################################################

def get_from_zmp(msg):
    try:
        ## Desired Force Profile on swing leg
        half_robot_weight = 864.75/2 # units [N], half robots weight without feet
        com_y_max = 0.085    #step_width  = 0.171/2         #0.095 # maximal movement of COM in y direction
        min_support_force = 200 # minimal weight that we want to keep on swing leg while shifting weight to stance leg
        desired_normal_force = half_robot_weight - abs(msg.com_ref.y/com_y_max) * (half_robot_weight - min_support_force)

        if ( msg.step_phase == 1 ) or ( msg.step_phase == 2 ): # left leg is stance
            # [mhx,lhy,uhz,kny,lax,uay]
            # PSC_left_swing_leg.ByPassON()# bypass controller
            # PSC_right_swing_leg.ByPassOFF()
            # swing_fixed = copy.deepcopy(msg.swing_foot)
            # swing_fixed.z = PSC_right_swing_leg.getCMD(msg.swing_foot.z, desired_normal_force)  
            
            # right_leg_angles = swing_leg_ik(swing_fixed,msg.swing_hip,msg.pelvis_m)
            right_leg_angles = swing_leg_ik(msg.swing_foot,msg.swing_hip,msg.pelvis_m)
            left_leg_angles = stance_leg_ik(msg.stance_hip,msg.pelvis_d)
        elif ( msg.step_phase == 3 ) or ( msg.step_phase == 4 ): # right leg is stance
            # [mhx,lhy,uhz,kny,lax,uay]
            # PSC_right_swing_leg.ByPassON()  # bypass controller
            # PSC_left_swing_leg.ByPassOFF()
            # swing_fixed = copy.deepcopy(msg.swing_foot)
            # swing_fixed.z = PSC_left_swing_leg.getCMD(msg.swing_foot.z, desired_normal_force) 

            # left_leg_angles = swing_leg_ik(swing_fixed,msg.swing_hip,msg.pelvis_m)
            left_leg_angles = swing_leg_ik(msg.swing_foot,msg.swing_hip,msg.pelvis_m)
            right_leg_angles = stance_leg_ik(msg.stance_hip,msg.pelvis_d)

    except IKReachException as exc:
        rospy.loginfo('IKException: %s leg is out of reach, req pos: %f ,%f, %f',exc.foot,exc.requested_pos[0],exc.requested_pos[1],exc.requested_pos[2])
        return

    ns.JC.set_pos('l_leg_lax', left_leg_angles[4] ) #JSC_l_leg_lax.getCMD(ns.LegAng.ang.lax) )
    ns.JC.set_pos('l_leg_uay', left_leg_angles[5] )
    ns.JC.set_pos('l_leg_kny', left_leg_angles[3] )
    ns.JC.set_pos('l_leg_uhz', left_leg_angles[2] )
    ns.JC.set_pos('l_leg_lhy', left_leg_angles[1] )
    ns.JC.set_pos('l_leg_mhx', left_leg_angles[0] ) #JSC_l_leg_mhx.getCMD(ns.LegAng.ang.mhx) )

    ns.JC.set_pos('r_leg_lax', right_leg_angles[4] ) #JSC_r_leg_lax.getCMD(ns.LegAng.ang.lax + lax_stance) )
    ns.JC.set_pos('r_leg_uay', right_leg_angles[5] )
    ns.JC.set_pos('r_leg_kny', right_leg_angles[3] )
    ns.JC.set_pos('r_leg_uhz', right_leg_angles[2] )
    ns.JC.set_pos('r_leg_lhy', right_leg_angles[1] )
    ns.JC.set_pos('r_leg_mhx', right_leg_angles[0] ) #JJSC_r_leg_mhx.getCMD(ns.LegAng.ang.mhx + mhx_stance) )
    ns.JC.send_command()

    #     rospy.loginfo("JC L_leg: lax = %f effort = %f, uay = %f, kny = %f, uhz = %f, lhy = %f, mhx = %f effort = %f, mby = %f, ubx= %f" %  \
    #                       (ns.LegAng.ang.lax, JSC_l_leg_lax.latest_effort, ns.LegAng.ang.uay, ns.LegAng.ang.kny, ns.LegAng.ang.uhz, \
    #                        ns.LegAng.ang.lhy, ns.LegAng.ang.mhx, JSC_l_leg_mhx.latest_effort, ns.LegAng.ang.mby, ns.LegAng.ang.ubx))

    


##########################################################################################
# request from joint_states publisher joints state to update Stiffness Controllers state #
##########################################################################################

# def get_joint_states(msg):
    
#     if JSC_l_leg_lax.JS_i == -1: # Update joint state indexs if not updated
#         try:
#             JSC_l_leg_lax.JS_i = msg.name.index(JSC_l_leg_lax.name)       
#             JSC_l_leg_mhx.JS_i = msg.name.index(JSC_l_leg_mhx.name)        
#             JSC_r_leg_lax.JS_i = msg.name.index(JSC_r_leg_lax.name)        
#             JSC_r_leg_mhx.JS_i = msg.name.index(JSC_r_leg_mhx.name)
        
#         except rospy.ROSInterruptException: pass
#         else:
#             rospy.loginfo(" update Stiffness Controllers JS_i - successful")

#     #rospy.loginfo("Stiffness Controllers joint state updated ")   

#######################################################################################
#                                 init publishers                                     #
#######################################################################################

def LEG_IK():

    rospy.init_node('LEG_IK')
    ns.JC = JointCommands_msg_handler()
    ns.RL = robot_listner()
    rospy.loginfo( "LEG_IK node is ready" )
    rospy.loginfo( "waiting 1 seconds for robot to initiate" )
    yaml_pth = os.path.join(roslib.packages.get_pkg_dir('C42_DRCSim2_tools'),'calibrated_controller_drc2_yuval.yaml')
    ns.JC.set_default_gains_from_yaml(yaml_pth)
    ns.JC.reset_gains()
    sub1=rospy.Subscriber("zmp_out", walking_trajectory, get_from_zmp) # traj, get_from_zmp)

    back_lbz = 0  
    back_mby = 0.06
    back_ubx = 0
    neck_ay = 0
    l_leg_uhz = 0 
    l_leg_mhx = -0.00096
    l_leg_lhy = -0.3564
    l_leg_kny = 0.6244
    l_leg_uay = -0.2680
    l_leg_lax = 0.0009
    r_leg_uhz = 0
    r_leg_mhx = -0.00096
    r_leg_lhy = -0.3564
    r_leg_kny = 0.6244
    r_leg_uay = -0.268
    r_leg_lax = 0.0009
    l_arm_usy = 0
    l_arm_shx = -1.3
    l_arm_ely = 0
    l_arm_elx = 0
    l_arm_uwy = 0
    l_arm_mwx = 0
    r_arm_usy = 0
    r_arm_shx = 1.3
    r_arm_ely = 0
    r_arm_elx = 0
    r_arm_uwy = 0
    r_arm_mwx = 0

    cur_pos = [ back_lbz, back_mby, back_ubx, neck_ay,
      l_leg_uhz, l_leg_mhx, l_leg_lhy, l_leg_kny, l_leg_uay, l_leg_lax,
      r_leg_uhz, r_leg_mhx, r_leg_lhy, r_leg_kny, r_leg_uay, r_leg_lax,
      l_arm_usy, l_arm_shx, l_arm_ely, l_arm_elx, l_arm_uwy, l_arm_mwx,
      r_arm_usy, r_arm_shx, r_arm_ely, r_arm_elx, r_arm_uwy, r_arm_mwx]
    # cur_pos = ns.RL.current_pos()
    ns.JC.set_all_pos(cur_pos)
    rospy.sleep(1)

    rospy.spin()

if __name__ == '__main__':

    LEG_IK()

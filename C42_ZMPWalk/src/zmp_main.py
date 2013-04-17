#!/usr/bin/env python

###################################################################################
####                                                                             ##
####  zmp_main.py                                                                ##
####  last updated - version 4.0, Yuval 08/4/2013                                ##
####                                                                             ##
####    run this script to initiate ZMP Walking Task                             ##
####    1) run Task: rosrun C42_ZMPWalk zmp_main.py                              ##
####     ( with other nodes: roslaunch C42_ZMPWalk zmp_walk.launch )             ##
####    2) run C31_clone to emulate the C31PathPlanner (publish a path message): ##
####       rosrun C42_ZMPWalk scripts/C31_Clone.py                               ##
####    3) start walking: rosrun C0_RobilTask task_tester ZmpWalk                ##
####    stops walking: i) when reached goal position (set by C31_PathPlanner).   ##
####                   ii) or preempted goal by task handler which will cause an ##
####                      Emergency Stop.                                        ##
####                                                                             ##
####    this node runs with parameters generated by matlab and are stored        ##
####    in the file '/src/parameters'.                                           ##
####    the walking patern in governed by the parameters:                        ##
####    step_length,step_width and step_time                                     ##
####                                                                             ##
###################################################################################     

import roslib; roslib.load_manifest('C42_ZMPWalk')
import rospy, sys #,os.path
from pylab import *
from C42_ZMPWalk.msg import walking_trajectory, Position, Orientation, Pos_and_Ori  #traj
from std_msgs.msg import Int32, Float64
from preview_controller import ZMP_Preview_Controller
from swing_trajectory import *
from zmp_profiles import *
from preview_buffer import ZMP_Preview_Buffer
import tf
import copy
from robot_state import Robot_State
from StepStateMachine import *
from ZmpLocalPathPlanner import *
from sensor_msgs.msg import Imu #Odometry
from RobilTaskPy import *
from threading import Lock
from nav_msgs.msg import Odometry
#from geometry_msgs.msg import Twist, Vector3
from C31_PathPlanner.msg import C31_Waypoints  

class MyTask(RobilTask):

    def __init__(self, name):
        print "Init ZmpWalk"
        RobilTask.__init__(self, name)

        self._Des_Orientation = 0#-math.pi/2

        rospy.sleep(1)
        self._listener = tf.TransformListener()

        self._walk = 0
        self._done = False

        # sampling time:
        self._rate = 100  # [Hz]
        self._dt = 1.0/self._rate # [sec] # sample time (was named time_step)
        self._interval = rospy.Rate(self._rate)

        self._out = walking_trajectory () #traj() # self._output message of topic 'zmp_self._out'

        self._max_step_time = 10.0 #[sec] the longest periodstep_length, of step that we plan to do

        # Preview Controllers:

        self._Sagital_x_Preview_Controller = ZMP_Preview_Controller('X_sagital','sagital_x',0.0) # name, parameters_folder_name, initial position of COM
        self._Lateral_y_Preview_Controller = ZMP_Preview_Controller('Y_lateral','lateral_y',0.0) # name, parameters_folder_name, initial position of COM

        self._NL = self._Lateral_y_Preview_Controller.getBufferSize()

        # Preview Buffers:
        self._Preview_Sagital_x = ZMP_Preview_Buffer('Sagital X', self._NL, 4*self._max_step_time/self._dt, 0 ) #name, preview_sample_size, max_step_samples, precede_time_samples
        self._Preview_Lateral_y = ZMP_Preview_Buffer('Lateral Y', self._NL, 4*self._max_step_time/self._dt, 0 ) #name, preview_sample_size, max_step_samples, precede_time_samples

        # init preview:step_length,
        self._p_ref_x = zeros(self._NL)
        self._p_ref_y = zeros(self._NL)

        # initialize swing trajectory object
        self._swing_traj = Swing_Trajectory('swing_foot_trajectory')

        # Robot State object:
        self._rs = Robot_State('Robot State')

        self._orientation_correction = Orientation_Control()

        self._ZmpStateMachine = StepStateMachine(self._rs,self._out,self._listener,self._Preview_Sagital_x,self._Preview_Lateral_y,self._swing_traj,self._rate,self._orientation_correction)

        self._ZmpLpp = LocalPathPlanner()

        ## RUN TOPICS:
        self._odom_sub = rospy.Subscriber('/ground_truth_odom',Odometry,self._odom_cb)
        self._path_sub = rospy.Subscriber('/C31PathPlanner',C31_Waypoints,self._path_cb)

        self._pub_zmp = rospy.Publisher('zmp_out', walking_trajectory ) #traj)
        self._pub_state = rospy.Publisher('zmp_state',Int32)
        self._pub_error = rospy.Publisher('zmp_error',Float64)
        self._sub_orientation_command = rospy.Subscriber('orientation_command' , Float64 , self._listn_to_orientation_command)

        self._imu_ori_z_sub = rospy.Subscriber('/atlas/imu', Imu, self._get_imu)  #Odometry, get_imu) 

        
    def _odom_cb(self,odom):
        self._done = self._ZmpLpp.UpdatePosition(odom.pose.pose.position.x,odom.pose.pose.position.y)
        
    def _path_cb(self,path):
        rospy.loginfo('got path %s',path)
        p = []
        for wp in path.points:
            p.append(Waypoint(wp.x,wp.y))
        self._ZmpLpp.SetPath(p)
    
    def _listn_to_orientation_command(self,orientation_command): 
        self._Des_Orientation = (orientation_command.data)*math.pi/180.0
        rospy.loginfo("recieved orientation command: orientation = %f" % (self._Des_Orientation) )
        rospy.loginfo("time:")
        rospy.loginfo(rospy.get_time())

    # init hip_z_orientation_controller
    def _get_imu(self,msg):  #listen to /atlas/imu/pose/pose/orientation
        self._imu_orientation = msg.orientation
        
    def task(self, name, uid, parameters):
        print "Start ZmpWalk"

        self._ZmpStateMachine.init_values()
        self._ZmpStateMachine.Initialize()
        self._ZmpStateMachine.Start()

        while not self._done:
            if self.isPreepted():
                self._ZmpStateMachine.EmergencyStop()
                print "Preempt ZmpWalk: EmergencyStop"
                self._ZmpStateMachine.EmergencyStop()
                return RTResult_PREEPTED()
            self._ZmpStateMachine.SetTurnCmd(turn_cmd = 30*math.pi/180)
            self._p_ref_x,self._p_ref_y,new_step_trigger_x,new_step_trigger_y = self._ZmpStateMachine.UpdatePreview()
            [COMx, COMx_dot, p_pre_con_x] = self._Sagital_x_Preview_Controller.getCOM_ref( self._p_ref_x,new_step_trigger_x )
            [COMy, COMy_dot, p_pre_con_y] = self._Lateral_y_Preview_Controller.getCOM_ref( self._p_ref_y,new_step_trigger_y )

            self._rs.getRobot_State(listener = self._listener)
            self._ZmpStateMachine.CalculateFootSwingTrajectory()
            #requiredYaw = self._Des_Orientation # ZmpLpp.GetTargetYaw()
            requiredYaw = self._ZmpLpp.GetTargetYaw()
            self._out = self._ZmpStateMachine.GetWalkingTrajectory(COMx, COMx_dot, p_pre_con_x,COMy, COMy_dot, p_pre_con_y,self._p_ref_x,self._p_ref_y,requiredYaw,self._imu_orientation)
            self._pub_zmp.publish(self._out)
            self._pub_state.publish(self._ZmpStateMachine.GetStateId())
            self._pub_error.publish(self._ZmpLpp.GetPathError())

            self._interval.sleep()

        self._ZmpStateMachine.EmergencyStop() #        self._ZmpStateMachine.Stop()

        print "Finish ZmpWalk"
        return RTResult_SUCCESSED("Finished in Success")

if __name__ == '__main__':
    rospy.init_node('C42_ZMPwalkNode')
    MyTask("ZmpWalk")
    rospy.spin()
    print "C42_ZMPwalkNode Closed"

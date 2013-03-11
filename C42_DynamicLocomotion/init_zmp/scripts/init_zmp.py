#!/usr/bin/env python

import roslib, time 
roslib.load_manifest('init_zmp')
import rospy, math, actionlib
import rosparam

import sys, os.path
import yaml
from pr2_mechanism_msgs.srv import *
from std_msgs.msg import *
from control_msgs.msg import *
from std_srvs.srv import Empty

load_controller = rospy.ServiceProxy('pr2_controller_manager/load_controller', LoadController)
unload_controller = rospy.ServiceProxy('pr2_controller_manager/unload_controller', UnloadController)
switch_controller = rospy.ServiceProxy('pr2_controller_manager/switch_controller', SwitchController)
list_loaded_controllers = rospy.ServiceProxy('pr2_controller_manager/list_controllers', ListControllers)
#reset_gazebo_model = 

loaded = []

 # <!--rostopic pub /r_arm_shx_position_controller/command std_msgs/Float64 "data: 1.3"/-->
  #<!--rostopic pub /l_arm_shx_position_controller/command std_msgs/Float64 "data: -1.3"/-->


position_controller_names = ['l_arm_elx_position_controller', 'r_arm_elx_position_controller', \
                             'l_arm_ely_position_controller', 'r_arm_ely_position_controller', \
                             'l_arm_mwx_position_controller', 'r_arm_mwx_position_controller', \
                             'l_arm_shx_position_controller', 'r_arm_shx_position_controller', \
                             'l_arm_usy_position_controller', 'r_arm_usy_position_controller', \
                             'l_arm_uwy_position_controller', 'r_arm_uwy_position_controller', \
                             'l_leg_kny_position_controller', 'r_leg_kny_position_controller', \
                             'l_leg_lax_position_controller', 'r_leg_lax_position_controller', \
                             'l_leg_lhy_position_controller', 'r_leg_lhy_position_controller', \
                             'l_leg_mhx_position_controller', 'r_leg_mhx_position_controller', \
                             'l_leg_uay_position_controller', 'r_leg_uay_position_controller', \
                             'l_leg_uhz_position_controller', 'r_leg_uhz_position_controller', \
                             'neck_ay_position_controller', 'back_lbz_position_controller', \
                             'back_mby_position_controller', 'back_ubx_position_controller' ]
atlas_controller_name = ['atlas_controller']

def init_pose_with_trajectory_controllers():
    #rospy.loginfo("Started: init_pose_with_trajectory_controllers")
    succeeded_to_init_pose = 0
    # rospy.init_node('init_traj')
    traj_client = actionlib.SimpleActionClient( '/atlas_controller/follow_joint_trajectory', \
                                 FollowJointTrajectoryAction)
    traj_client.wait_for_server()
    goal = FollowJointTrajectoryGoal()
    traj_len = 1 #2 #1
    goal.trajectory.joint_names = ['l_leg_uhz', 'l_leg_mhx', 'l_leg_lhy', 
                                   'l_leg_kny', 'l_leg_uay', 'l_leg_lax', 
                                   'r_leg_uhz', 'r_leg_mhx', 'r_leg_lhy', 
                                   'r_leg_kny', 'r_leg_uay', 'r_leg_lax', 
                                   'l_arm_usy', 'l_arm_shx', 'l_arm_ely', 
                                   'l_arm_elx', 'l_arm_uwy', 'l_arm_mwx', 
                                   'r_arm_usy', 'r_arm_shx', 'r_arm_ely', 
                                   'r_arm_elx', 'r_arm_uwy', 'r_arm_mwx', 
                                   'neck_ay', 'back_lbz', 'back_mby', 'back_ubx']
    goal.trajectory.points = [ trajectory_msgs.msg.JointTrajectoryPoint() \
                             for x in xrange(0, traj_len) ]
    t = 0.0
    traj_positions = [ [0] * 28 ]
    # init_pose = rospy.get_param("/zmp_walking/zmp_init_pose")
    # traj_positions.append( [ init_pose['l_leg_uhz'], init_pose['l_leg_mhx'], init_pose['l_leg_lhy'], 
    #                                init_pose['l_leg_kny'], init_pose['l_leg_uay'], init_pose['l_leg_lax'], 
    #                                init_pose['r_leg_uhz'], init_pose['r_leg_mhx'], init_pose['r_leg_lhy'], 
    #                                init_pose['r_leg_kny'], init_pose['r_leg_uay'], init_pose['r_leg_lax'], 
    #                                init_pose['l_arm_usy'], init_pose['l_arm_shx'], init_pose['l_arm_ely'], 
    #                                init_pose['l_arm_elx'], init_pose['l_arm_uwy'], init_pose['l_arm_mwx'], 
    #                                init_pose['r_arm_usy'], init_pose['r_arm_shx'], init_pose['r_arm_ely'], 
    #                                init_pose['r_arm_elx'], init_pose['r_arm_uwy'], init_pose['r_arm_mwx'], 
    #                                init_pose['neck_ay'], init_pose['back_lbz'], init_pose['back_mby'], init_pose['back_ubx'] ] )
    for i in xrange(0, traj_len):
        goal_pt = goal.trajectory.points[i]
        t += 1 #5
        goal_pt.time_from_start = rospy.Duration.from_sec(t)
        goal_pt.velocities = [0] * 28
        #y = "0 0 -0.2372 0.4491 -0.2119 0   0 0 -0.2372 0.4491 -0.2119 0   0 -1.3 0 0 0 0   0 1.3 0 0 0 0    0 0 0 0"
        #goal_pt.positions = [ float(x) for x in y.split() ]
        goal_pt.positions = traj_positions[i]
    
    traj_client.send_goal(goal)
    traj_client.wait_for_result(rospy.Duration.from_sec(t + 1)) #3
    succeeded_to_init_pose = 1
    return succeeded_to_init_pose

def ResetControllerParams(running_controller_names, new_controller_names, New_params_yaml_file_name):
    #yaml_file_with_path = os.path.join(os.getcwd(), r"/data_yaml/", New_params_yaml_file_name)
    [pathname, Script_File_Name] = os.path.split(sys.argv[0]) #os.path.dirname(sys.argv[0])
    #rospy.loginfo("Path - HEAD:  %s TAIL:  %s" % (pathname, Script_File_Name) )
    [Sub_pathname, Script_Folder] = os.path.split(pathname)
    #rospy.loginfo("Sub-Path - HEAD:  %s TAIL:  %s" % (Sub_pathname, Script_Folder) ) 
    yaml_file_with_path = os.path.join(Sub_pathname, r"data_yaml/", New_params_yaml_file_name)
    #yaml_file_with_path = os.path.join(yaml_file_with_path, New_params_yaml_file_name)
    rospy.loginfo("Data file path: %s" % yaml_file_with_path)
    if os.path.exists(yaml_file_with_path):
        # load yaml file onto the parameter server, using the namespace specified in the yaml file
        rosparam.set_param("",open(yaml_file_with_path))
        rospy.loginfo("Found file: %s" % New_params_yaml_file_name)
    
    # unload loaded controllers that we want to load (inorder to reset params)
    loaded_list_resp = list_loaded_controllers()
    rospy.loginfo("List of loaded controllers: %s" % ', '.join(loaded_list_resp.controllers))

    # make sure running_controller_names are running and new_controller_names are stopped
    flag_running_is_stopped = 0 
    for index, loaded_name in enumerate(loaded_list_resp.controllers): 
        if loaded_name in running_controller_names:
            if loaded_list_resp.state[index] == 'stopped':
                flag_running_is_stopped = 1
    if flag_running_is_stopped:
        resp = switch_controller(running_controller_names, new_controller_names, 2)
        if resp.ok != 0:
            rospy.loginfo("Running controller: %s" % ', '.join(running_controller_names ))
            rospy.loginfo("Stoped controllers: %s" % ', '.join(new_controller_names))
            time.sleep(0.01)
            move_2_init_pose = init_pose_with_trajectory_controllers()
            if move_2_init_pose == 1:
                rospy.loginfo("Successful init pose with trajectory controllers:")
            else:
                rospy.loginfo("Failed to init pose with trajectory controllers:")

        else:
            rospy.logerr("Failed to run controllers: %s" % ', '.join(running_controller_names ))

    #for index, loaded_name in enumerate(loaded_list_resp.controllers):
    #    if loaded_name in running_controller_names:
    #        if loaded_list_resp.state[index] == 'stopped':
    #            resp = switch_controller(loaded_name, [], 2)
    #            if resp.ok != 0:
    #                rospy.loginfo("Running controller: %s" % loaded_name)
    #            else:
    #                rospy.logerr("Failed to run controllers: %s" % loaded_name)


    #for index, loaded_name in enumerate(loaded_list_resp.controllers):
    #    rospy.loginfo("Num in list of loaded controllers: idex= %d; controller='%s' " % (index, loaded_name) ) 

    # load new_controller_names
    for name in new_controller_names:
        if name in loaded_list_resp.controllers:
            try: # if found loaded controller try to unload it
                #switch_controller([], name, SwitchControllerRequest.STRICT)
                rospy.logout("Trying to unload %s" % name)
                unload_controller(name)
                rospy.logout("Succeeded in unloading %s" % name)
            except rospy.ServiceException:
                rospy.logwarn("joint_control_legs couldn't reach pr2_controller_manager to take down controllers.")
        resp = load_controller(name)
        if resp.ok != 0:
            loaded.append(name)
        else:
            time.sleep(0.1) # give error message a chance to get out
            rospy.logerr("Failed to load %s" % name)

    rospy.loginfo("Loaded controllers: %s" % ', '.join(loaded))

    #if rospy.is_shutdown():
    #    return


    # start controllers is requested
    resp = switch_controller(loaded, running_controller_names, 2)
    if resp.ok != 0:
        rospy.loginfo("Started controllers: %s" % ', '.join(loaded))
        rospy.loginfo("Stoped controllers: %s" % ', '.join(running_controller_names))
    else:
        rospy.logerr("Failed to start controllers: %s" % ', '.join(loaded))
 

def jointStateCommand():
    # Setup the publishers for each joint
    #r_arm_elx = rospy.Publisher('/r_arm_elx_position_controller/command', Float64)
    #r_arm_ely = rospy.Publisher('/r_arm_ely_position_controller/command', Float64)
    l_leg_kny = rospy.Publisher('/l_leg_kny_position_controller/command', Float64)
    r_leg_kny = rospy.Publisher('/r_leg_kny_position_controller/command', Float64)

    l_leg_lax = rospy.Publisher('/l_leg_lax_position_controller/command', Float64)
    r_leg_lax = rospy.Publisher('/r_leg_lax_position_controller/command', Float64)
    
    l_leg_lhy = rospy.Publisher('/l_leg_lhy_position_controller/command', Float64)
    r_leg_lhy = rospy.Publisher('/r_leg_lhy_position_controller/command', Float64)

    l_leg_mhx = rospy.Publisher('/l_leg_mhx_position_controller/command', Float64)
    r_leg_mhx = rospy.Publisher('/r_leg_mhx_position_controller/command', Float64)

    l_leg_uay = rospy.Publisher('/l_leg_uay_position_controller/command', Float64)
    r_leg_uay = rospy.Publisher('/r_leg_uay_position_controller/command', Float64)
   
    l_leg_uhz = rospy.Publisher('/l_leg_uhz_position_controller/command', Float64)
    r_leg_uhz = rospy.Publisher('/r_leg_uhz_position_controller/command', Float64)

    neck_ay = rospy.Publisher('/neck_ay_position_controller/command', Float64)
    back_lbz = rospy.Publisher('/back_lbz_position_controller/command', Float64)  
    back_mby = rospy.Publisher('/back_mby_position_controller/command', Float64)
    back_ubx = rospy.Publisher('/back_ubx_position_controller/command', Float64)

    l_arm_elx = rospy.Publisher('/l_arm_elx_position_controller/command', Float64)
    r_arm_elx = rospy.Publisher('/r_arm_elx_position_controller/command', Float64)

    l_arm_ely = rospy.Publisher('/l_arm_ely_position_controller/command', Float64)
    r_arm_ely = rospy.Publisher('/r_arm_ely_position_controller/command', Float64)

    l_arm_mwx = rospy.Publisher('/l_arm_mwx_position_controller/command', Float64)
    r_arm_mwx = rospy.Publisher('/r_arm_mwx_position_controller/command', Float64)
    
    l_arm_shx = rospy.Publisher('/l_arm_shx_position_controller/command', Float64)
    r_arm_shx = rospy.Publisher('/r_arm_shx_position_controller/command', Float64)

    l_arm_usy = rospy.Publisher('/l_arm_usy_position_controller/command', Float64)
    r_arm_usy = rospy.Publisher('/r_arm_usy_position_controller/command', Float64)

    l_arm_uwy = rospy.Publisher('/l_arm_uwy_position_controller/command', Float64)
    r_arm_uwy = rospy.Publisher('/r_arm_uwy_position_controller/command', Float64)
   
    rospy.loginfo(": Setup Joint Control Publishers")
    # Initialize the node
    #rospy.init_node('joint_control_init')

    #Initial pose
     
  # # bend down 5cm from IK
  #   #bend_hip_angle = -0.3734 
  #   #bend_knee_angle = 0.7059
  #   #bend_ankle_angle = -0.3325
  
  # # bend down 2cm from IK
  #   bend_hip_angle =0# -0.2372 
  #   bend_knee_angle = 0#0.4491
  #   bend_ankle_angle = 0#-0.2119


    zero_pose_l_leg_kny = 0.0 #bend_knee_angle
    zero_pose_r_leg_kny = 0.0 #zero_pose_l_leg_kny
    
    zero_pose_l_leg_lax = 0.0 #0.0
    zero_pose_r_leg_lax = 0.0 #zero_pose_l_leg_lax

    zero_pose_l_leg_lhy = 0.0 #bend_hip_angle 
    zero_pose_r_leg_lhy = 0.0 #zero_pose_l_leg_lhy

    zero_pose_l_leg_mhx = 0.0 #0.0
    zero_pose_r_leg_mhx = 0.0 #zero_pose_l_leg_mhx
    
    zero_pose_l_leg_uay = 0.0 #bend_ankle_angle
    zero_pose_r_leg_uay = 0.0 #zero_pose_l_leg_uay

    zero_pose_l_leg_uhz = 0.0 #0.0
    zero_pose_r_leg_uhz = 0.0 #zero_pose_l_leg_uhz

    zero_pose_neck_ay =  0.0 #0.0
    zero_pose_back_lbz = 0.0 #0.0
    zero_pose_back_mby = 0.0 #0.0
    zero_pose_back_ubx = 0.0 #0.0 

    zero_pose_l_arm_elx = 0.0 
    zero_pose_r_arm_elx = 0.0
    
    zero_pose_l_arm_ely = 0.0 
    zero_pose_r_arm_ely = 0.0 

    zero_pose_l_arm_mwx = 0.0 
    zero_pose_r_arm_mwx = 0.0 

    zero_pose_l_arm_shx = 0.0 
    zero_pose_r_arm_shx = 0.0 
    
    zero_pose_l_arm_usy = 0.0 
    zero_pose_r_arm_usy = 0.0 

    zero_pose_l_arm_uwy = 0.0 
    zero_pose_r_arm_uwy = 0.0 

    # # insert step command on init:
    # enable_step_flag = 0
    # step_pose_l_leg_lhy = -0.1
    # step_pose_r_leg_lhy = step_pose_l_leg_lhy

    times_to_pub_zero_pose = 100 #1000 # number of times to publish zero_pose
    pub_num = 1;

    while ( not rospy.is_shutdown() ) and (pub_num < times_to_pub_zero_pose):
    # intitialsation publish:
        l_leg_kny.publish(zero_pose_l_leg_kny)
        r_leg_kny.publish(zero_pose_r_leg_kny)
    
        l_leg_lax.publish(zero_pose_l_leg_lax)
        r_leg_lax.publish(zero_pose_r_leg_lax)
        
        l_leg_lhy.publish(zero_pose_l_leg_lhy)
        r_leg_lhy.publish(zero_pose_r_leg_lhy)
    
        l_leg_mhx.publish(zero_pose_l_leg_mhx)
        r_leg_mhx.publish(zero_pose_r_leg_mhx)
    
        l_leg_uay.publish(zero_pose_l_leg_uay)
        r_leg_uay.publish(zero_pose_r_leg_uay)
    
        l_leg_uhz.publish(zero_pose_l_leg_uhz)
        r_leg_uhz.publish(zero_pose_r_leg_uhz)
    
        neck_ay.publish(zero_pose_neck_ay)
        back_lbz.publish(zero_pose_back_lbz)
        back_mby.publish(zero_pose_back_mby)
        back_ubx.publish(zero_pose_back_ubx)
    
        l_arm_elx.publish(zero_pose_l_arm_elx)
        r_arm_elx.publish(zero_pose_r_arm_elx)
    
        l_arm_ely.publish(zero_pose_l_arm_ely)
        r_arm_ely.publish(zero_pose_r_arm_ely)
        
        l_arm_mwx.publish(zero_pose_l_arm_mwx)
        r_arm_mwx.publish(zero_pose_r_arm_mwx)
    
        l_arm_shx.publish(zero_pose_l_arm_shx)
        r_arm_shx.publish(zero_pose_r_arm_shx)
    
        l_arm_usy.publish(zero_pose_l_arm_usy)
        r_arm_usy.publish(zero_pose_r_arm_usy)
    
        l_arm_uwy.publish(zero_pose_l_arm_uwy)
        r_arm_uwy.publish(zero_pose_r_arm_uwy)

        pub_num += 1
        # Wait 0.01 second
        rospy.sleep(0.01)



    # Final Position:
    init_pose = rospy.get_param("/zmp_walking/zmp_init_pose")

    final_pose_l_leg_kny = init_pose['l_leg_kny'] #bend_knee_angle
    final_pose_r_leg_kny = init_pose['r_leg_kny'] #zero_pose_l_leg_kny
    
    final_pose_l_leg_lax = init_pose['l_leg_lax'] #0.0
    final_pose_r_leg_lax = init_pose['r_leg_lax'] #zero_pose_l_leg_lax

    final_pose_l_leg_lhy = init_pose['l_leg_lhy'] #bend_hip_angle 
    final_pose_r_leg_lhy = init_pose['r_leg_lhy'] #zero_pose_l_leg_lhy

    final_pose_l_leg_mhx = init_pose['l_leg_mhx'] #0.0
    final_pose_r_leg_mhx = init_pose['r_leg_mhx'] #zero_pose_l_leg_mhx
    
    final_pose_l_leg_uay = init_pose['l_leg_uay'] #bend_ankle_angle
    final_pose_r_leg_uay = init_pose['r_leg_uay'] #zero_pose_l_leg_uay

    final_pose_l_leg_uhz = init_pose['l_leg_uhz'] #0.0
    final_pose_r_leg_uhz = init_pose['r_leg_uhz'] #zero_pose_l_leg_uhz

    final_pose_neck_ay =  init_pose['neck_ay'] #0.0
    final_pose_back_lbz = init_pose['back_lbz'] #0.0
    final_pose_back_mby = init_pose['back_mby'] #0.0
    final_pose_back_ubx = init_pose['back_ubx'] #0.0 

    final_pose_l_arm_elx = init_pose['l_arm_elx']
    final_pose_r_arm_elx = init_pose['r_arm_elx']
    
    final_pose_l_arm_ely = init_pose['l_arm_ely']
    final_pose_r_arm_ely = init_pose['r_arm_ely']

    final_pose_l_arm_mwx = init_pose['l_arm_mwx']
    final_pose_r_arm_mwx = init_pose['r_arm_mwx']

    final_pose_l_arm_shx = init_pose['l_arm_shx']
    final_pose_r_arm_shx = init_pose['r_arm_shx']
    
    final_pose_l_arm_usy = init_pose['l_arm_usy']
    final_pose_r_arm_usy = init_pose['r_arm_usy']

    final_pose_l_arm_uwy = init_pose['l_arm_uwy']
    final_pose_r_arm_uwy = init_pose['r_arm_uwy']

    #t_start = rospy.get_time() # current time to start Init
    #init_duration = 30 # units [sec]; time to enable Init
    #t = t_start
    times_to_pub = 600 #1000 # number of times to publish
    final_pose_pub = 500.0 # number of times to publish until reaching final position
    #times_to_step = 500
    pub_num = 1;

    #Sleep for 0.1 second to wait for the home position
    rospy.sleep(0.1)

    rospy.wait_for_service('gazebo/reset_models')
    reset_gazebo_model = rospy.ServiceProxy('gazebo/reset_models', Empty)
    reset_gazebo_model()

    pose_input = zero_pose_l_leg_lhy
    #This while loop will continue until ROS tells it to shutdown init time passes
    while ( not rospy.is_shutdown() ) and (pub_num < times_to_pub): #( t <= (t_start + 10) ):
        if pub_num < final_pose_pub:
            final_ratio = pub_num/final_pose_pub
        else:
            final_ratio = 1.0
        pub_num += 1
        
        #t = rospy.get_time() #6 * rospy.get_time()
        #elbow_x = -1.57 + 0.4 * math.cos(t)
        #elbow_y = 0.4 + 0.4 * math.sin(t)
        #r_arm_elx.publish(elbow_x)
        #r_arm_ely.publish(elbow_y)
        
        # rospy.loginfo(": Pub num %d; final_ratio = %f" %(pub_num, final_ratio))

        # # Insertr Step command:
        # if (pub_num == times_to_step) and enable_step_flag:
        #     pose_input = step_pose_l_leg_lhy
        #     rospy.loginfo(": Starting step with size %f in publication number %d" %(pose_input,pub_num))

        l_leg_kny.publish( final_pose_l_leg_kny*final_ratio + zero_pose_l_leg_kny*(1-final_ratio) )
        r_leg_kny.publish( final_pose_r_leg_kny*final_ratio + zero_pose_r_leg_kny*(1-final_ratio) )

        l_leg_lax.publish( final_pose_l_leg_lax*final_ratio + zero_pose_l_leg_lax*(1-final_ratio) )
        r_leg_lax.publish( final_pose_r_leg_lax*final_ratio + zero_pose_r_leg_lax*(1-final_ratio) )
    
        l_leg_lhy.publish( final_pose_l_leg_lhy*final_ratio + zero_pose_l_leg_lhy*(1-final_ratio) ) # zero_pose_l_leg_lhy #pose_input
        r_leg_lhy.publish( final_pose_r_leg_lhy*final_ratio + zero_pose_r_leg_lhy*(1-final_ratio) ) # zero_pose_r_leg_lhy #pose_input

        l_leg_mhx.publish( final_pose_l_leg_mhx*final_ratio + zero_pose_l_leg_mhx*(1-final_ratio) )
        r_leg_mhx.publish( final_pose_r_leg_mhx*final_ratio + zero_pose_r_leg_mhx*(1-final_ratio) )

        l_leg_uay.publish( final_pose_l_leg_uay*final_ratio + zero_pose_l_leg_uay*(1-final_ratio) )
        r_leg_uay.publish( final_pose_r_leg_uay*final_ratio + zero_pose_r_leg_uay*(1-final_ratio) )

        l_leg_uhz.publish( final_pose_l_leg_uhz*final_ratio + zero_pose_l_leg_uhz*(1-final_ratio) )
        r_leg_uhz.publish( final_pose_r_leg_uhz*final_ratio + zero_pose_r_leg_uhz*(1-final_ratio) )

        neck_ay.publish( final_pose_neck_ay*final_ratio + zero_pose_neck_ay*(1-final_ratio) )
        back_lbz.publish( final_pose_back_lbz*final_ratio + zero_pose_back_lbz*(1-final_ratio) )
        back_mby.publish( final_pose_back_mby*final_ratio + zero_pose_back_mby*(1-final_ratio) )
        back_ubx.publish( final_pose_back_ubx*final_ratio + zero_pose_back_ubx*(1-final_ratio) )

        l_arm_elx.publish( final_pose_l_arm_elx*final_ratio + zero_pose_l_arm_elx*(1-final_ratio) )
        r_arm_elx.publish( final_pose_r_arm_elx*final_ratio + zero_pose_r_arm_elx*(1-final_ratio) )

        l_arm_ely.publish( final_pose_l_arm_ely*final_ratio + zero_pose_l_arm_ely*(1-final_ratio) )
        r_arm_ely.publish( final_pose_r_arm_ely*final_ratio + zero_pose_r_arm_ely*(1-final_ratio) )
    
        l_arm_mwx.publish( final_pose_l_arm_mwx*final_ratio + zero_pose_l_arm_mwx*(1-final_ratio) ) # zero_pose_l_leg_lhy #pose_input
        r_arm_mwx.publish( final_pose_r_arm_mwx*final_ratio + zero_pose_r_arm_mwx*(1-final_ratio) ) # zero_pose_r_leg_lhy #pose_input

        l_arm_shx.publish( final_pose_l_arm_shx*final_ratio + zero_pose_l_arm_shx*(1-final_ratio) )
        r_arm_shx.publish( final_pose_r_arm_shx*final_ratio + zero_pose_r_arm_shx*(1-final_ratio) )

        l_arm_usy.publish( final_pose_l_arm_usy*final_ratio + zero_pose_l_arm_usy*(1-final_ratio) )
        r_arm_usy.publish( final_pose_r_arm_usy*final_ratio + zero_pose_r_arm_usy*(1-final_ratio) )

        l_arm_uwy.publish( final_pose_l_arm_uwy*final_ratio + zero_pose_l_arm_uwy*(1-final_ratio) )
        r_arm_uwy.publish( final_pose_r_arm_uwy*final_ratio + zero_pose_r_arm_uwy*(1-final_ratio) )


        # Wait 0.01 second
        rospy.sleep(0.01)


if __name__ == '__main__':
    rospy.init_node('init_zmp')
    rospy.loginfo("started init_zmp node")

    # Set parameters for ZMP_walking init position
    # # old params - bend_knees=0.04
    # rospy.set_param("/zmp_walking/zmp_init_pose", {'l_leg_uhz':0, 'l_leg_mhx':0, 'l_leg_lhy':-0.2372, 
    #                                'l_leg_kny':0.4491, 'l_leg_uay':-0.2119, 'l_leg_lax':0, 
    #                                'r_leg_uhz':0, 'r_leg_mhx':0, 'r_leg_lhy':-0.2372, 
    #                                'r_leg_kny':0.4491, 'r_leg_uay':-0.2119, 'r_leg_lax':0, 
    #                                'l_arm_usy':0, 'l_arm_shx':-1.3, 'l_arm_ely':0, 
    #                                'l_arm_elx':0, 'l_arm_uwy':0, 'l_arm_mwx':0, 
    #                                'r_arm_usy':0, 'r_arm_shx':1.3, 'r_arm_ely':0, 
    #                                'r_arm_elx':0, 'r_arm_uwy':0, 'r_arm_mwx':0, 
    #                                'neck_ay':0, 'back_lbz':0, 'back_mby':0, 'back_ubx':0})
    ## new params - bend_knees=0.18
    rospy.set_param("/zmp_walking/zmp_init_pose", {'l_leg_uhz':0, 'l_leg_mhx':0, 'l_leg_lhy':-0.7297, 
                                   'l_leg_kny':1.3677, 'l_leg_uay':-0.6380, 'l_leg_lax':0, 
                                   'r_leg_uhz':0, 'r_leg_mhx':0, 'r_leg_lhy':-0.7297, 
                                   'r_leg_kny':1.3677, 'r_leg_uay':-0.6380, 'r_leg_lax':0, 
                                   'l_arm_usy':0, 'l_arm_shx':-1.3, 'l_arm_ely':0, 
                                   'l_arm_elx':0, 'l_arm_uwy':0, 'l_arm_mwx':0, 
                                   'r_arm_usy':0, 'r_arm_shx':1.3, 'r_arm_ely':0, 
                                   'r_arm_elx':0, 'r_arm_uwy':0, 'r_arm_mwx':0, 
                                   'neck_ay':0, 'back_lbz':0, 'back_mby':0, 'back_ubx':0})
    ## new params - bend_knees=0.18, hip_sagital = 0.05 !!! collapses !!!
    # rospy.set_param("/zmp_walking/zmp_init_pose", {'l_leg_uhz':0, 'l_leg_mhx':0, 'l_leg_lhy':-0.7763, 
    #                                'l_leg_kny':1.492, 'l_leg_uay':-0.7139, 'l_leg_lax':0, 
    #                                'r_leg_uhz':0, 'r_leg_mhx':0, 'r_leg_lhy':-0.7763, 
    #                                'r_leg_kny':1.492, 'r_leg_uay':-0.7139, 'r_leg_lax':0, 
    #                                'l_arm_usy':0, 'l_arm_shx':-1.3, 'l_arm_ely':0, 
    #                                'l_arm_elx':0, 'l_arm_uwy':0, 'l_arm_mwx':0, 
    #                                'r_arm_usy':0, 'r_arm_shx':1.3, 'r_arm_ely':0, 
    #                                'r_arm_elx':0, 'r_arm_uwy':0, 'r_arm_mwx':0, 
    #                                'neck_ay':0, 'back_lbz':0, 'back_mby':0, 'back_ubx':0})
    # #for debug: off-set values for IK
    rospy.set_param("/zmp_walking/IK_zero_pose", {'l_leg_uhz':0, 'l_leg_mhx':0, 'l_leg_lhy':-0.13, 
                                   'l_leg_kny':0.13, 'l_leg_uay':0.0, 'l_leg_lax':0, 
                                   'r_leg_uhz':0, 'r_leg_mhx':0, 'r_leg_lhy':-0.13, 
                                   'r_leg_kny':0.13, 'r_leg_uay':0.0, 'r_leg_lax':0, 
                                   'l_arm_usy':0, 'l_arm_shx':-1.3, 'l_arm_ely':0, 
                                   'l_arm_elx':0, 'l_arm_uwy':0, 'l_arm_mwx':0, 
                                   'r_arm_usy':0, 'r_arm_shx':1.3, 'r_arm_ely':0, 
                                   'r_arm_elx':0, 'r_arm_uwy':0, 'r_arm_mwx':0, 
                                   'neck_ay':0, 'back_lbz':0, 'back_mby':0, 'back_ubx':0})

    move_2_init_pose = init_pose_with_trajectory_controllers()
    if move_2_init_pose == 1:
        rospy.loginfo("Successful init pose with trajectory controllers:")
    else:
        rospy.loginfo("Failed to init pose with trajectory controllers:")    

    try:
        ResetControllerParams(atlas_controller_name, position_controller_names, 'position_controllers.yaml')
    except rospy.ROSInterruptException as ex: 
        print ex

    try:
        jointStateCommand()
    except rospy.ROSInterruptException as ex: 
        print ex
        #pass



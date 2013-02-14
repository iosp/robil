#!/bin/sh
#This script should run the modules needed for testing C31

CURR_WD=$PWD
PKILL=$CURR_WD'/.killC51test.txt'
rm $PKILL
#roslaunch atlas_utils atlas_golf_cart_fire_hose.launch
#rostopic pub /drc_world/robot_enter_car geometry_msgs/Pose "position (press TAB)
echo "Starting executer"
rosrun C34_Executer executer &
C34_PID=$!
echo $C34_PID
echo "Done "
sleep 1
rosrun C22_GroundRecognitionAndMapping C22 &
C22_PID=$!
echo $C22_PID
sleep 3
echo "Starting C31"
rosrun C31_PathPlanner gpp&
C31_PID=$!
echo $C31_PID
echo "Done "
echo $C22_PID $C31_PID $C34_PID >> $PKILL

roscd C34_Executer
rosservice call executer/run T $PWD/tmp/pln
rosservice call executer/resume T
rosservice call executer/run T1 $PWD/tmp/pln1
rosservice call executer/resume T1
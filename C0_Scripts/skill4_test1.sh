#!/bin/sh
#This script should start the skill4 test
echo Start the skill4 test

CURR_WD=$PWD
PKILLS=$CURR_WD'/.skill4_test1.txt'
rm $PKILLS

#roslaunch atlas_utils atlas_drc_vehicle_fire_hose.launch &

roslaunch C51_CarOperation C51_completeLuanch.launch &
C51_PID=$!
echo $C51_PID
sleep 30

#start executor
rosrun C34_Executer executer &
$C34_Executer_PID=$!
echo $C34_Executer_PID
sleep 10

#start Designer
#roslaunch C34_Designer start.launch &
#$C34_Designer_PID=$!
#echo $C34_Designer_PID
#sleep 10

# start the perception modules:
# C21 C22 C24 C25
./perception.sh &
sleep 10

# start the object recognition module: C23
./objectRec.sh
#echo "Object Recognition started"

# start the object recognition module: C46
# T B D
#     OR
# Temporary
rostopic pub --once /drc_world/robot_enter_car geometry_msgs/Pose '{}'
sleep 5

#start the pathplanner module: C31
#./withPathtest.sh
rosrun C31_PathPlanner gpp&
$C31_PID=$!
echo $C31_PID
#sleep 5

echo $C51_PID >> $PKILLS
echo $C51_PID $C34_Executer_PID  $C31_PID >> $PKILLS

#rosservice call executer/run T4 /home/userws1/git/robil/C34_Designer/plans/skill4_test1_without_pathplanning.xml 
rosservice call executer/run T4 /home/userws1/git/robil/C34_Designer/plans/skill4_driving.xml 
rosservice call executer/resume T4







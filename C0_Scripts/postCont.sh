#!/bin/sh
#This script should start the perception modules

CURR_WD=$PWD
PKILL=$CURR_WD'/.pc.txt'
rm $PKILL

echo "Starting Perception"
roslaunch C25_GlobalPosition C25.launch &
C25_PID=$!
echo $C25_PID
sleep 3
rosrun C31_PathPlanner qual > gpp.log &
C31_PID=$!
echo $C31_PID
echo "Starting DRCSim tools"
rosrun C42_DRCSim2_tools foot_contact_filter.py &
C42T_PID=$!
echo "Starting C45"
roslaunch C45_PostureControl C45_PostureControl.launch &
C45_PID=$!
echo $C25_PID $C42T_PID $C45_PID >> $PKILL
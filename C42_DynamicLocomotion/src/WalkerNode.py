#!/usr/bin/env python

from DynamicLocomotion import *
from WalkingModeChooser import *

import sys

###################################################################################
# File created by David Dovrat, 2013.
# For Robil, under project Robil's license of choice
# The code in this file is provided "as is" and comes with no warranty whatsoever
###################################################################################

if __name__ == '__main__':
#    walkingMode = 'BDI'
#    try:
#        opts, args = getopt.getopt(sys.argv[1:],"m:",["mode="])
#    except getopt.GetoptError:
#        print 'WalkerNode.py -mode <QS or DD or BDI>'
#        sys.exit(2)
#    for opt, arg in opts:
#        if opt in ("-m", "--mode"):
#            if arg in ('BDI','QS','DD'):
#                walkingMode = arg
#            else:
#               print (arg, " not recognized as a walking mode")

    try:
        walkingMode = sys.argv[1]
    except Exception:
        print "Usage: WalkingMode.py <Option>"
        print "Options are:"
        print " CD for Dynamic Continuous mode"
        print " QS for Discrete Quasi-Static mode"
        print " DD for Discrete Dynamic mode"
        print " DW for DW mode"
        print " AP for Aline Pose mode"
        sys.exit(2)
    if walkingMode in ('CD'):
        rospy.init_node('WalkerNode_Continuous')       
        walkingModeChooser = WalkingModeChooser(walkingMode)
        node = DynamicLocomotion("WalkerNode_Continuous",walkingModeChooser)
        print "WalkerNode_Continuous TASK created"
        rospy.spin()
    elif walkingMode in ('QS','DD'):
        rospy.init_node('WalkerNode_Discrete')       
        walkingModeChooser = WalkingModeChooser(walkingMode)
        node = DynamicLocomotion("WalkerNode_Discrete",walkingModeChooser)
        print "WalkerNode_Discrete TASK created"
        rospy.spin()
    elif walkingMode in ('DW'):
        rospy.init_node('WalkerNode_DW')       
        walkingModeChooser = WalkingModeChooser(walkingMode)
        node = DynamicLocomotion("WalkerNode_DW",walkingModeChooser)
        print "WalkerNode walk on four TASK created"
        rospy.spin()
    elif walkingMode in ('AP'):
        rospy.init_node('WalkerNode_AP')       
        walkingModeChooser = WalkingModeChooser(walkingMode)
        node = DynamicLocomotion("WalkerNode_AP",walkingModeChooser)
        print "WalkerNode Discrete Aline Pose mode TASK created"
        rospy.spin()
    else:
        print "Usage: WalkingMode.py <Option>"
        print "Options are:"
        print " CD for Dynamic Continuous mode"
        print " QS for Discrete Quasi-Static mode"
        print " DD for Discrete Dynamic mode"
        print " DW for DW mode"
        print " AP for Aline Pose mode"
    print "WalkerNode Closed"

               
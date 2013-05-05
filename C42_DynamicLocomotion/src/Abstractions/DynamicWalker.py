#!/usr/bin/env python
import rospy
from WalkingMode import *
from WalkingModeChooserInterface import *
from LocalPathPlanner import *

###################################################################################
# File created by David Dovrat, 2013.
# For Robil, under project Robil's license of choice
# The code in this file is provided "as is" and comes with no warranty whatsoever
################################################################################### 

class DynamicWalker(object):
    
    def __init__(self,walkingModeChooser,localPathPlanner):
        self._ModeChooser = walkingModeChooser
        self._LPP = localPathPlanner


    # Commands:
    def Initialize(self):
        self._WalkingMode = self._ModeChooser.GetRecommendedMode()
        self._WalkingMode.Initialize()
        
    def Start(self):
        pass
    
    def Walk(self):
        self._WalkingMode.StartWalking()
        self._WalkingMode.Walk()
        return True
    
    def Stop(self):
        self._WalkingMode.Stop()
        self._LPP.Stop()

    def SetPath(self,Path):
        self._LPP.SetPath(Path)


    # Status:
    def IsDone(self):
        return self._WalkingMode.IsDone()

    def IsReady(self):
        return self._LPP.IsActive()





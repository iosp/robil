#!/usr/bin/env python

###################################################################################
# File created by David Dovrat, 2013.
# For Robil, under project Robil's license of choice
# The code in this file is provided "as is" and comes with no warranty whatsoever
###################################################################################

from Abstractions.WalkingModeChooserInterface import *
from Abstractions.Interface_tf import *
from BDI.WalkingModeBDI import *
from QS.QS_WalkingMode import *
from DD.DD_WalkingMode import *
from DW.DW_WalkingMode import *
from LocalPathPlanner import *

class WalkingModeChooserEnum:
    DontCare,BDI,QS,DD = range(4)

class WalkingModeChooser(WalkingModeChooserInterface):

    def __init__(self,prefferedMode,bIsDoingQual=False):
        # Once we clean bIsDoingQual out of the code, we can allow for the lpp to be known only to the concrete walking
        # mode
        lpp = LocalPathPlanner()
        lpp.SetDoingQual(bIsDoingQual)
        iTf = Interface_tf()
        
        self._Modes = {'BDI':WalkingModeBDI(lpp),'QS':QS_WalkingMode(iTf),'DD':DD_WalkingMode(iTf),'DW':DW_WalkingMode(iTf)}
        self._Preferred = prefferedMode
        self._CurrentMode = prefferedMode
        self._Recommended = prefferedMode
        self._OverRide = WalkingModeChooserEnum.DontCare
        self._bIsAppropriate = True
        
        self._debug_cmd_sub = rospy.Subscriber('walker_mode_override',Int32,self._walker_mode_handler)
        
    def IsCurrentModeAppropriate(self):
        self._bIsAppropriate = True
        if (WalkingModeChooserEnum.DontCare != self._OverRide):
            if self._CurrentMode in ('QS','DD'):
                if (WalkingModeChooserEnum.DD == self._OverRide):
                    if ('QS' == self._CurrentMode):
                       self._bIsAppropriate = False
                    self._Recommended = 'DD'
                else:
                    if ('DD' == self._CurrentMode):
                       self._bIsAppropriate = False
                    self._Recommended = 'QS'
        # Always appropriate when done
        elif(False == self._Modes[self._CurrentMode].IsDone()):
            path = self._Modes[self._CurrentMode].GetPath()
            # If the preferred mode is fit, that means current is inappropriate if current is not preferred
            if (self._Preferred == self._CurrentMode):
                if (True == self._Modes[self._Preferred].Fitness(path)):
                    self._bIsAppropriate = True
                else:
                    self._bIsAppropriate = False
                    if ('QS' == self._Preferred):
                        self._Recommended = 'DD'
                    elif ('DD' == self._Preferred):
                        self._Recommended = 'QS'
            elif (True == self._Modes[self._Preferred].Fitness(path)):
                self._bIsAppropriate = False
                self._Recommended = self._Preffered
            else:
                self._bIsAppropriate = (True == self._Modes[self._CurrentMode].Fitness(path))
        return self._bIsAppropriate;
    
    def GetRecommendedMode(self):
        result = self._Modes[self._CurrentMode]
        if (False == self._bIsAppropriate):
            path = self._Modes[self._CurrentMode].GetPath()
            result = False
            if (True == self._Modes[self._Recommended].Fitness(path)):
                self._Modes[self._Recommended].SetPath(path)
                result = self._Modes[self._Recommended]
        return result
    
    def _walker_mode_handler(self,walker_mode):
        self._OverRide = walker_mode.data



# -*- coding: utf-8 -*-
"""
TskNode class inherits from node class.
type of node- tsk
doesn't have children
and has it own run function
"""

from Node import node



class TskNode (node):
    def __init__(self,treeInst,mytree,parent):
        #tsk id is it's name        
        self.Id = treeInst.get("name")
        #call to super-condstracture
        node.__init__(self,treeInst,mytree,"tsk",parent)
        #upsate distributions from xml file
#        self.distTableSucc = self.createDistTable("Successdistribution")
#        self.distTableFail = self.createDistTable("Failuredistribution")
           
        
        
        
    # tsk-run    
    def run (self, index):
        debug = node.run(self, index)
        if (debug!=None):
            return debug             
        a = [True, 0]        
        a[0]= self.getRandomProb(index)	
        if a[0]:
            a[1] = round(self.getDistSuccByIndex(index).calcProb())
        else:
            a[1] = round(self.getDistFailByIndex(index).calcProb())      
        return a
        
    #override the node func- tsk doesn't have children   
    def getChild(self,index):
         return None
         
    #override the node func- tsk doesn't have children      
    def getChildren (self):
        return None
        
        
     #override the node func   
    def setDEBUGnode(self,sSucc=None,sTime=None):
        node.DEBUGnode(None,None)
        self.DEBUG = [sSucc,sTime]
    
    
    #override the node func- check for tsk etree and then in the plan etree 
    def getAttrib(self,parm):
        #try to get string attributes from tsk etree in myTree
        stringAttrib = self.myTree.getTskAttrib(self.Id,parm)
        #if faild- return none, try to take string attributes from plan tree by calling node method-getAttrib
        if stringAttrib == None:
            stringAttrib = node.getAttrib(self,parm)

        return stringAttrib


   
            
'''
Created on 27 paŸ 2014

@author: Piotr
'''
from inverseKinematics import *
from time import *

class DrOctopus(object):
    L1 = 0.3
    L2 = 0.24
    Xstart = 0.0
    Ystart = (L1+L2)-0.1
    Zstart = 0.0
    armSpacing = 0.60
    clockStarts =[0,0,0,0]
    curves = [[],[],[],[]]
    counters=[0,0,0,0]

    def __init__(self):
        self.arms=[]
        for i in range(4):
            self.arms.append(inverseKinematics(self.L1, self.L2))
        
        
    def run(self):
        Xmax = self.armSpacing/2 - .04
        Ymax = (self.L1+self.L2)-0.1
        while 1:
            for limits in [[[0.0, Xmax], [0.0, Ymax], [0.0, Xmax]], [[0.0, Xmax*4.0/3.0], [0.0, Ymax], [0.0, Xmax*2.0/3.0]], [[0.0, Xmax*2.0/3.0], [0.0, Ymax], [0.0, Xmax*4.0/3.0]]]:
                for i in range(4):
                    self.arms[i].limitTo(limits)
                for t in range(6000): # 10 min
                    self.checkSensors()
                    # according to sensors
                    # load curves if changed
                    for i in range(4):
                        if time.clock() >= self.curves[i][self.counters[i]][2] + self.clockStarts[i]:
                            pass # next point 
            
    def checkSensors(self):

if __name__ == '__main__':
    pass
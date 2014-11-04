'''
Created on 27.10.2014

@author: Piotr
'''
from inverseKinematics import *
from time import *
import serial

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
    port = 13

    def __init__(self):
        self.arms=[]
        for i in range(4):
            self.arms.append(inverseKinematics(self.L1, self.L2))
            self.arms[i].angleLimits=[[math.radians(-60), math.radians(60)], [math.radians(-60), math.radians(60)],
                                      [0, math.radians(120)],[math.radians(-90), math.radians(30)]]
        self.ser = serial.Serial(self.port, 115200)
        print self.ser

    def armGoToAngle(self, nArm, angles, time):
        nArm=int(nArm)
        if (nArm<0):
            nArm=0
        if nArm>3:
            nArm=3
        (self.arms[nArm].A0, self.arms[nArm].A1, self.arms[nArm].A2, self.arms[nArm].A3) = angles
        self.arms[nArm].checkAngles()
        self.armSend(nArm, time)

    def armGoToPos(self, nArm, pos, time):
        nArm=int(nArm)
        self.arms[nArm].moveTo(pox[0], pox[1], pox[2])
        self.armSend(nArm, time)

    def armSend(self, nArm, time):
        nArm=int(nArm)
        ik = self.arms[nArm]
        A = [ik.A0, ik.A1, ik.A2, ik.A3]
        command = ""
        for i in range(4):
            servo = int((A[i] - ik.angleOffsets[i])* 700.0 / math.radians(60)) + 1500
            command+= "#%d P%d " %(nArm*4 + i, servo)
        command+= "T%d\r" % time
        print command
        self.ser.write(command)
        
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
        pass
    
if __name__ == '__main__':
    pass

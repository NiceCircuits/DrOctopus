#-*- coding: utf-8 -*-
'''
Created on 27.10.2014

@author: Piotr
'''
from inverseKinematics import *
import serial, os, random, re
import threading, time, math

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
    port_inner=17
    port_outter=16
    senOffset = [0,0,0,20,10,900,0]
    senDiv = [90,10,1,0.2,0.07,0.5,10]
    senNames=["Akcelerometr", "Magnetometr", "Odległościomierz", "Wilgotność", "Temperatura", "Ciśnienie", "Swiatło"]
    

    def __init__(self):
        self.arms=[]
        for i in range(4):
            self.arms.append(inverseKinematics(self.L1, self.L2))
            self.arms[i].angleLimits=[[0, math.radians(90)], [math.radians(-60), math.radians(60)],
                                      [0, math.radians(120)],[math.radians(-90), math.radians(30)]]
        self.ser = serial.Serial(self.port, 115200)
        self.sensors = [0]*7
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

    def loadLine(self, group): # random line
        path = "line/%d/" % group
        files = os.listdir(path)
        path += files[random.randrange(len(files))]
        f = open(path)
        lines = f.readlines()
        points = [map(int, re.findall(r'\d+', line)) for line in lines]
        x=[p[0] for p in points]
        y=[p[1] for p in points]
        # scale
        xnew = [(xp-min(x))*100.0/(max(x+y)-min(x)) for xp in x]
        ynew = [(yp-min(y))*100.0/(max(x+y)-min(y)) for yp in y]
        for i in range(len(points)):
            points[i][0]=xnew[i]
            points[i][1]=ynew[i]
        return points

    def sensorsCheck(self):
        ser1=serial.Serial(self.port_inner, 115200)
        ser2=serial.Serial(self.port_outter, 115200)
        while(1):
            time.sleep(1)
            line=ser1.readline().strip() + "," + ser2.readline().strip()
            ser1.flushInput()
            ser2.flushInput()
            self.sensors=map(int, re.findall(r'\d+', line))+[0]*7
            print(self.sensors)
            for i in range(7):
                self.sensors[i]=int(math.fabs((math.fabs(self.sensors[i])-self.senOffset[i])/self.senDiv[i]))
            print(self.sensors)
            
    def run(self):
        Xmax = self.armSpacing/2 - .04
        Ymax = (self.L1+self.L2)-0.1
        threading.Thread(target=self.sensorsCheck).start()
        while 0:
            for limits in [[[0.0, Xmax], [0.0, Ymax], [0.0, Xmax]], [[0.0, Xmax*4.0/3.0], [0.0, Ymax], [0.0, Xmax*2.0/3.0]], [[0.0, Xmax*2.0/3.0], [0.0, Ymax], [0.0, Xmax*4.0/3.0]]]:
                for i in range(4):
                    self.arms[i].limitTo(limits)
                for t in range(6000): # 10 min
                    # according to sensors
                    # load curves if changed
                    for i in range(4):
                        if time.clock() >= self.curves[i][self.counters[i]][2] + self.clockStarts[i]:
                            pass # next point
            
    
if __name__ == '__main__':
    pass

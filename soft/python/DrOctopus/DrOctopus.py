#-*- coding: utf-8 -*-
'''
Created on 27.10.2014

@author: Piotr
'''
from inverseKinematics import *
import serial, os, random, re
import threading, time, math

wzrost = 171
waga = 69
wiek = 49
plec = "m"

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
    port = 6
    port_inner=8
    port_outter=7
    senOffset = [0,0,0,20,10,900,0]
    senDiv = [90,10,1,0.2,0.07,0.5,10]
    senNames=["Akcelerometr", "Magnetometr", "Odleglosciomierz", "Wilgotnosc", "Temperatura", "Cisnienie", "Swiatlo"]
    lengths = [0,0]
    arm=[0,0]
    

    def __init__(self):
        self.arms=[]
        for i in range(4):
            self.arms.append(inverseKinematics(self.L1, self.L2))
            self.arms[i].angleLimits=[[0, math.radians(90)], [math.radians(0), math.radians(120)],
                                      [math.radians(45), math.radians(165)],[math.radians(90), math.radians(200)]]
        self.ser = self.openSerial(self.port)
        try:
            self.ser1=self.openSerial(self.port_inner)
            self.ser2=self.openSerial(self.port_outter)
        except:
            pass
        self.sensors = [[0]*7]*20

    def extrude(self, number, on):
        if on:
            d = 24255
        else:
            d=24000
        command = "#%d p%d T100\r" %(16+int(number), d)
        self.ser.write(command)
        

    def openSerial(self, number):
        s = serial.Serial()
        s.port = number;
        s.baudrate=115200;
        try:
            s.open()
        except:
            s.close()
            s.open()
        print s
        return s

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
        print pos
        self.arms[nArm].moveTo(pos[0], pos[1], pos[2])
        self.armSend(nArm, time)

    def armSend(self, nArm, time):
        nArm=int(nArm)
        ik = self.arms[nArm]
        A = [ik.A0, ik.A1, ik.A2, ik.A3]
        command = ""
        for i in range(4):
            if ik.inverts[i]:
                mul = -1
            else:
                mul=1
            servo = mul*int((A[i] - ik.angleOffsets[i])* 700.0 / math.radians(60)) + 1500
            command+= "#%d P%d " %(nArm*4 + i, servo)
        command+= "T%d\r" % int(time*1000)
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
        while(1):
            time.sleep(1)
            line = ""
            try:
                line=self.ser1.readline().strip() + "," + self.ser2.readline().strip()
                self.ser1.flushInput()
                self.ser2.flushInput()
                sensors=map(int, re.findall(r'\d+', line))+[0]*7
                for i in range(7):
                    sensors[i]=int(math.fabs((math.fabs(float(self.sensors[i])-self.senOffset[i]))/self.senDiv[i]))
            except:
                sensors = [int(random.randrange(255)) for i in range(7)]
            self.sensors.pop(0)
            self.sensors.append(sensors)
            f=open(r"C:\Users\ASP\Desktop\MapaEkran\OdSensorow.txt","w")
            for s in self.sensors:
                for i in range(7):
                    kol = ["transparentny", "bialy", "szary", "czarny"]
                    leng=["bardzo dluga", "dluga", "krotka", "bardzo krotka"]
                    speed = ["bardzo szybko", "szybko", "wolno", "bardzo wolno"]
                    if(s[i]<75):
                        n=0
                    elif(s[i]<150):
                        n=1
                    elif(s[i]<225):
                        n=2
                    else:
                        n=3
                    f.write("%s,%d,%s,%s,%s\n" % (self.senNames[i], s[i],kol[n], leng[n], speed[n]))
            #print(self.sensors)

    def close(self):
        try:
            self.ser.close()
            self.ser1.close()
            self.ser2.close()
        except:
            pass
            
    def run(self):
        Xmax = self.armSpacing/2 - .04
        Ymax = (self.L1+self.L2)-0.1
        threading.Thread(target=self.sensorsCheck).start()
        for k in range(4):
            self.extrude(k,1)
        start = time.time()
        y=self.L1+self.L2-0.02
        while time.time()<(start+3600):
            for i in range(wiek):
                print i
                pts = self.loadLine(int(random.randrange(1,3)))
                for k in range(4):
                    self.armGoToPos(k,[pts[0][0]*float(wzrost)/4.0/1000.0, y, pts[0][1]*float(waga)/2.0/1000.0], 1)
                time.sleep(1)
                tt=0
                for p in pts:
                    for k in range(4):
                        tt = p[2]/1000.0 - tt
                        self.armGoToPos(k,[p[0]*float(wzrost)/4.0/10000.0, y, p[1]*float(waga)/2.0/10000.0], tt)
                    time.sleep(tt+.01)
            y+=.005
        while time.time()<(start+56000):
            for i in range(wiek):
                print i
                sense = self.sensors[random.randrange(len(self.sensors))]
                ss = sense[random.randrange(len(sense))]
                ss = int(ss*256/4)
                if ss>3:
                    ss=3
                if ss<0:
                    ss=0
                pts = self.loadLine(ss+1)
                for k in range(4):
                    self.armGoToPos(k,[pts[0][0]*float(wzrost)/4.0/1000.0, y, pts[0][1]*float(waga)/2.0/1000.0], 1)
                time.sleep(1)
                tt=0
                for p in pts:
                    for k in range(4):
                        tt = p[2]/1000.0 - tt
                        self.armGoToPos(k,[p[0]*float(wzrost)/4.0/10000.0, y, p[1]*float(waga)/2.0/10000.0], tt)
                    time.sleep(tt+.01)
            y+=.005
                    
    
if __name__ == '__main__':
    pass

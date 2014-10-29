'''
Created on 27.10.2014

@author: Piotr
'''

'''
           A0 (horizontal plane), Z - axis ortogonal to X, Y
           |
          ,-.  (0,0)
         ( / .......
          |-'
          /  A1
         /
        |
        / L1
       /
      |
    ,-/ A2
   ( +-..__
    `-'    ``--..___  ,-.
            L2      ``-+ ) (X,Y)
                   A3 `+'
                       |
                      +++
                      | |
                      +-+
'''

import math

class inverseKinematics(object):

    def __init__(self, L1, L2):
        self.L1 = float(L1)
        self.L2 = float(L2)
        self.A0 = 0.0
        self.A1 = math.radians(180.0)
        self.A2 = math.radians(180.0)
        self.A3 = math.radians(90.0)
        self.X = float(L1+L2)
        self.Y = 0.0
        self.Z = 0.0
        self.limits=[[self.X, self.X], [0.0,0.0], [0.0,0.0]]
        
    def limitTo(self, value, limits):
        if (value<limits[0]):
            return limits[0]
        elif (value>limits[1]):
            return limits[1]
        else:
            return value
        
    def moveTo(self, X, Y, Z):
        X = self.limitTo(float(X), self.limits[0])
        Y = self.limitTo(float(Y), self.limits[1])
        Z = self.limitTo(float(Z), self.limits[2])
        # inverse kinematics - rotate plane XY in Z axis
        self.A0 = math.atan2(Z, X) # rotation in Z axis
        # Inverse kinematics in rotated plane
        Xrot = math.sqrt(X*X+Z*Z) 
        L = math.sqrt(Xrot*Xrot+Y*Y) # length from (0,0) to (X,Y)
        LtoLMax = L/(self.L1+self.L2)
        if(LtoLMax >=1):
            L = L / LtoLMax *0.999
            Xrot = Xrot / LtoLMax *0.999
            Y = Y / LtoLMax *0.999
        AL = math.atan2(Y, Xrot) # angle between X axis and L
        ALL1 = math.acos((self.L1*self.L1 - self.L2*self.L2 + L*L)/2/self.L1/L) # angle between L1 and L
        self.A1 = AL + ALL1
        self.A2 = math.acos((self.L1*self.L1 + self.L2*self.L2 - L*L)/2/self.L1/self.L2)
        self.A3 = self.A1 + self.A2 - math.radians(90.0)
        # Forward Kinematics - sanity check
        X1rot = self.L1*math.cos(self.A1) #position of first joint
        Y1 = self.L1*math.sin(self.A1)
        A2abs = self.A1 + self.A2 -math.radians(180.0) #first angle - absolute, between X and L2
        Xrot = (X1rot + self.L2*math.cos(A2abs)) 
        self.X = Xrot*math.cos(self.A0) 
        self.Y = Y1 + self.L2*math.sin(A2abs)
        self.Z = Xrot*math.sin(self.A0)
        self._X1=X1rot*math.cos(self.A0)  # for debug purposes
        self._Y1=Y1
        



















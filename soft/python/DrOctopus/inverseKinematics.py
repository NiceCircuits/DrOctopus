'''
Created on 27.10.2014

@author: Piotr
'''

'''
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
    '''
    classdocs
    '''

    def __init__(self, L1, L2):
        '''
        Constructor
        '''
        self.L1 = float(L1)
        self.L2 = float(L2)
        self.A1 = 180.0
        self.A2 = 180.0
        self.A3 = 90.0
        self.X = float(L1+L2)
        self.Y = 0.0
        
    def moveTo(self, X, Y):
        X=float(X)
        Y=float(Y)
        # Inverse kinematics
        L = math.sqrt(X*X+Y*Y) # length from (0,0) to (X,Y)
        LtoLMax = L/(self.L1+self.L2)
        if(LtoLMax >=1):
            L = L / LtoLMax *0.999
            X = X / LtoLMax *0.999
            Y = Y / LtoLMax *0.999
        AL = math.atan2(Y, X) # angle between X axis and L
        ALL1 = math.acos((self.L1*self.L1 - self.L2*self.L2 + L*L)/2/self.L1/L) # angle between L1 and L
        self.A1 = AL + ALL1
        self.A2 = math.acos((self.L1*self.L1 + self.L2*self.L2 - L*L)/2/self.L1/self.L2)
        self.A3 = self.A1 + self.A2 - math.radians(90.0)
        # Forward Kinematics - sanity check
        X1 = self.L1*math.cos(self.A1) #position of first joint
        Y1 = self.L1*math.sin(self.A1)
        A2abs = self.A1 + self.A2 -math.radians(180.0) #first angle - absolute, between X and L2 
        self.X = X1 + self.L2*math.cos(A2abs)
        self.Y = Y1 + self.L2*math.sin(A2abs)
        self._X1=X1 # for debug purposes
        self._Y1=Y1



















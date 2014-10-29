'''
Created on 27.10.2014

@author: Piotr
'''
from inverseKinematics import *

if __name__ == '__main__':
    ik = inverseKinematics(1,1)
    ik.moveTo(0, 1, -1)
    print ["%0.3f"%f for f in [ik._X1, ik._Y1]]
    print ["%0.3f"%f for f in [ik.X, ik.Y, ik.Z]]
    print ["%0.3f"%f for f in[ik.A0, ik.A1, ik.A2, ik.A3]]

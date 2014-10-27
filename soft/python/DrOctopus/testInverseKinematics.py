'''
Created on 27.10.2014

@author: Piotr
'''
from inverseKinematics import *


if __name__ == '__main__':
    ik = inverseKinematics(1,1)
    ik.moveTo(0.5, 0.5)
    print([0, ik._X1, ik.X], [0, ik._Y1, ik.Y])
    print [ik.A1, ik.A2, ik.A3]

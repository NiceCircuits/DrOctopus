'''
Created on 27.10.2014

@author: Piotr
'''
from inverseKinematics import *

if __name__ == '__main__':
    ik = inverseKinematics(1,1)
#     ik.moveTo(1, 1)
#     print [[ik._X1, ik._Y1], [ik.X, ik.Y]]
#     print [ik.A1, ik.A2, ik.A3]
#     ik.moveTo(1.4, 1.4)
#     print [[ik._X1, ik._Y1], [ik.X, ik.Y]]
#     print [ik.A1, ik.A2, ik.A3]
#     ik.moveTo(2, 2)
#     print [[ik._X1, ik._Y1], [ik.X, ik.Y]]
#     print [ik.A1, ik.A2, ik.A3]
#     ik.moveTo(1.6, 0.8)
#     print [[ik._X1, ik._Y1], [ik.X, ik.Y]]
#     print [ik.A1, ik.A2, ik.A3]
    ik.moveTo(2, 1)
    print [[ik._X1, ik._Y1], [ik.X, ik.Y]]
    print [ik.A1, ik.A2, ik.A3]
    ik.moveTo(1, 1)
    print [[ik._X1, ik._Y1], [ik.X, ik.Y]]
    print [ik.A1, ik.A2, ik.A3]

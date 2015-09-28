'''
Created on 27.10.2014

@author: Piotr
'''
from DrOctopus import *
import matplotlib.pyplot as plt
import time

if __name__ == '__main__':
    d = DrOctopus()
    d.run()
    if 0:
        d.extrude(1,1)
        time.sleep(1)
        d.extrude(1,0)
    if 0:
        for i in range(4):
            for j in range(3):
                d.armGoToPos(j+1, [0.2, 0.3, i*0.05], 1)
            time.sleep(2)
        #plt.plot([0, d.arms[2]._X1, d.arms[2].X], [0, d.arms[2]._Y1, d.arms[2].Y])
        #plt.show()
        #d.armGoToAngle(2, [0, 1,3,1],1)
        #time.sleep(1)
        #d.armGoToAngle(2, [0, 1,3,3],1)
    time.sleep(10)
    if 0:
        d.close()
        del d

    

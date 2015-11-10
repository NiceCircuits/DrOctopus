'''
Created on 27.10.2014

@author: Piotr
'''
from DrOctopus import *
import matplotlib.pyplot as plt
import time, math

if __name__ == '__main__':
    d = DrOctopus()
    d.run(False)
    if 0:
        d.extrude(1,1)
        time.sleep(1)
        d.extrude(1,0)
    if 0:
        d.armGoToPos(2, [0.1,0.44,0],3)
        time.sleep(1)
        plt.plot([0, d.arms[2]._X1, d.arms[2].X], [0, d.arms[2]._Y1, d.arms[2].Y])
        plt.show()
    #time.sleep(10)
    if 0:
        d.close()
        del d

    
#0 P1025 #1 P1884 #2 P861 #3 P1362 T1000
#16 p24140 T100
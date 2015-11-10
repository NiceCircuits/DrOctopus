'''
Created on 27.10.2014

@author: Piotr
'''
from DrOctopus import *
import matplotlib.pyplot as plt
import time, math

if __name__ == '__main__':
    d = DrOctopus()
    for i in range(4):
        d.armGoToAngle(i, [math.radians(45),math.radians(90),math.radians(180),math.radians(180)],1)
    time.sleep(1)

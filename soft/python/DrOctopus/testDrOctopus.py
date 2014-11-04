'''
Created on 27.10.2014

@author: Piotr
'''
from DrOctopus import *
import matplotlib.pyplot as plt
import time

if __name__ == '__main__':
    d = DrOctopus()
    for i in range(100):
        d.armGoToAngle(1, [0.0, 0, 0, 0], 2000)
        time.sleep(2.5)
        d.armGoToAngle(1, [1, 0.5, 0.5, 1], 2000)
        time.sleep(2.5)
        

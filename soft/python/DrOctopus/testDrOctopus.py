'''
Created on 27.10.2014

@author: Piotr
'''
from DrOctopus import *
import matplotlib.pyplot as plt
import time

if __name__ == '__main__':
    d = DrOctopus()
    for i in range(10):
        pn=d.loadLine(4)
        x=[p[0] for p in pn]
        y=[p[1] for p in pn]
        plt.plot(x,y, ".")
    plt.show()
    d.ser.close()
    

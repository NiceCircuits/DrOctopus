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
    d.ser.close()

    

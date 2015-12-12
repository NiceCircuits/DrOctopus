# -*- coding: utf-8 -*-
"""
Created on Tue Nov 10 20:30:02 2015

@author: piotr at nicecircuits.com
"""

# -*- coding: utf-8 -*-
from __future__ import print_function # compatibility with python 2 and 3
__author__ = 'piotr'
import paho.mqtt.client as mqtt
import serial, time, re, logging, numpy, math
server = "test.mosquitto.org"
port = 1883
global received, ids, lastId, log, ser, client

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("/drOctopus/resp/#")
    #client.subscribe("/esp-link/#")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    global received, ids, lastId, log
    temp="topic: " + msg.topic + " " + "  message: " + str(msg.payload)
    log.debug(temp)

def kill_mqtt():
    global client
    client.disconnect()
    
def sendCommand(timestamp, positions):
    global client
    arr=[(timestamp>>(i))&0xff for i in [0,8,16,24]]
    for p in positions:
        arr=arr+[(p>>(i))&0xff for i in [0,8]]
    print([timestamp, positions])
    client.publish("/drOctopus/arm/1", bytearray(arr))
    
def syncTime(newTime):
    global client
    arr=[(newTime>>(i))&0xff for i in [0,8,16,24]]
    print("Sync time: %d" % newTime)
    client.publish("/drOctopus/common/sync", bytearray(arr))    
    
def tester_init():
    global received, ids, lastId, log, ser, client
    #enable debug logs
    log=logging.getLogger()
    log.setLevel(logging.DEBUG)
    formatter=logging.Formatter('%(asctime)s - %(message)s')
    logfile=logging.FileHandler("log.txt","w")
    logfile.setLevel(logging.INFO)
    logfile.setFormatter(formatter)
    console = logging.StreamHandler()
    console.setLevel(logging.DEBUG)
    console.setFormatter(formatter)
    log.addHandler(console)
    log.addHandler(logfile)
    
    client = mqtt.Client(protocol=3)
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect_async(server, port, 60)
    
    log.info("Application start")
    client.loop_start()

if __name__ =="__main__":
    global client
    tester_init()
    time.sleep(1)
    syncTime(0)
    if 1:
        for k in range(1):
            for i in range(100000):
                sendCommand(i*500,[0,0,int(math.sin(i*math.pi/500)*300),0])
                if i>10:
                    time.sleep(.499)
        time.sleep(1)

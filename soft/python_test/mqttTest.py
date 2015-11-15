# -*- coding: utf-8 -*-
"""
Created on Tue Nov 10 20:30:02 2015

@author: piotr at nicecircuits.com
"""

# -*- coding: utf-8 -*-
from __future__ import print_function # compatibility with python 2 and 3
__author__ = 'piotr'
import paho.mqtt.client as mqtt
import serial, time, re, logging, numpy
server = "test.mosquitto.org"
port = 1883
global received, ids, lastId, log, ser, client

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("/drOctopus/test/#")
    client.subscribe("/esp-link/#")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    global received, ids, lastId, log
    temp="topic: " + msg.topic + " " + "  message: " + str(msg.payload)
    log.debug(temp)

def kill_mqtt():
    client.disconnect()
    
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
    tester_init()
    time.sleep(1)
    for i in range(100):
        client.publish("/drOctopus/test/testsssss", "aaa")
        time.sleep(5)

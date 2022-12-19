#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import requests

IP = "10.0.0.226"

class Rover:
    def __init__(self, ip):
        self.ip = ip

        self.left_speed = 0
        self.right_speed = 0
        self.yaw = 0
        self.pitch = 0
    
    def send_command(self):
        self.send_data(self.left_speed, self.right_speed, self.yaw, self.pitch)
    
    def send_data(self, left_speed, right_speed, yaw, pitch):
        params = {
            "left_speed" : left_speed,
            "right_speed" : right_speed,
            "yaw" : yaw,
            "pitch" : pitch,
        }
        #CHANGE TO POST IN ESP CODE
        requests.get("http://" + self.ip, params=params)
    
    def set_speed(self, left_speed, right_speed):
        self.set_left_speed(left_speed)
        self.set_right_speed(right_speed)
    
    def set_left_speed(self, speed):
        self.left_speed = speed
    
    def set_right_speed(self, speed):
        self.right_speed = speed


def main():
    import time
    io = Rover(IP)
    io.set_speed(255,255)
    io.send_command()
    time.sleep(1)
    io.set_speed(-255,-255)
    io.send_command()
    time.sleep(1)
    io.set_speed(0,0)
    io.send_command()

if __name__ == "__main__":
    main()
#!/bin/bash

#Installation of the necessary tools

sudo apt update
sudo apt install can-utils

#Load kernel module (only once)
sudo modprobe vcan

#If you need to load can_raw (the protocol used by SocketCAN):
sudo modprobe can
sudo modprobe can_raw

#Create virtual vcan interface
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0

#if you want to delete vcan0
#sudo ip link delete vcan0
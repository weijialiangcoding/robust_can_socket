#!/bin/bash
/sbin/ip link set can1 down
/sbin/ip link set can3 down

/sbin/ip link set can1 type can bitrate 1000000 restart-ms 100
/sbin/ip link set can3 type can bitrate 1000000 restart-ms 100

/sbin/ip link set can1 up
/sbin/ip link set can3 up

#!/bin/sh
ifconfig eth0 192.168.99.98 netmask 255.255.255.0
sleep 1
route add default gw 192.168.99.1
sleep 1 
mount 192.168.99.139:/root /mnt -o nolock

mount 192.168.99.139:/root/uukit/udp/embedMode /mnt -o nolock
sleep 1 
cd /system/init/driver && insmod sensor_jxf22.ko

cd /system/init/driver && insmod sinfo.ko

cd /system/init/driver && insmod tx-isp.ko

sleep 1
mount -t jffs2 /dev/mtdblock4 /opt
sleep 3

export LD_LIBRARY_PATH=/mnt/ukit_em/t20_demo/run:/system/lib


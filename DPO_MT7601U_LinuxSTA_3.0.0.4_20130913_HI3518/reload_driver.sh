#!/bin/bash

dhclient -r
ifconfig ra0 down
modprobe -r mt7601Usta
rmdir -r /etc/Wireless/RT2870STA/

cd /home/ubuntu/drv_mod/DPO_MT7601U_LinuxSTA_3.0.0.4_20130913_HI3518

make clean
make
sudo make install
sudo mkdir -p /etc/Wireless/RT2870STA/
sudo cp RT2870STA.dat /etc/Wireless/RT2870STA/
sudo modprobe mt7601Usta

ifconfig ra0 up
dhclient ra0

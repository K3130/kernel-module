#!/bin/bash

set -e

if [ -z "$1" ]; then
    echo "Usage: $0 <IP_ADDRESS>"
    exit 1
fi

IP_ADDR=$1

IP_A=$(echo $IP_ADDR | tr '.' ' ' | awk '{print $1}')
IP_B=$(echo $IP_ADDR | tr '.' ' ' | awk '{print $2}')
IP_C=$(echo $IP_ADDR | tr '.' ' ' | awk '{print $3}')
IP_D=$(echo $IP_ADDR | tr '.' ' ' | awk '{print $4}')

clear
make

dmesg -c > /dev/null 2>&1

insmod vnetint.ko ip_a=${IP_A} ip_b=${IP_B} ip_c=${IP_C} ip_d=${IP_D}
dmesg -c

ip addr show vnetint0

ping -c 5 ${IP_ADDR}


echo ""
echo "========================================="
echo "Press ENTER to remove module and clean up..."
echo "========================================="
read -r

rmmod vnetint
dmesg -c
make clean

echo ""
echo "Done!"
#!/bin/sh


if (whiptail --title "Server Setup" --yesno "Welcome to Server Setup (RTP-2 Project)." 8 78); then
    echo "User selected Yes, exit status was $?."
else
    echo "User selected No, exit status was $?."
    exit 0
fi

Msg_Count=$(whiptail --inputbox "Enter the Message Count" 8 39 --title "Messgae count input" 3>&1 1>&2 2>&3)
exitstatus=$?
if [ $exitstatus = 0 ]; then
    echo "Entered Count " $Msg_Count
else
    echo "Cancel."
    exit 0
fi

if (whiptail --title "" --yesno "Do you want to start server binary." 8 78); then
    echo "User selected Yes, exit status was $?."
else
    echo "User selected No, exit status was $?."
fi
exitstatus=$?
if [ $exitstatus = 0 ]; then
	cd build/
    	make 
	./server $Msg_Count
	cd -	
else
    echo "Cancel."
    exit 0
fi

sudo fdisk -l

sleep 5


Mount=$(whiptail --inputbox "Enter the external drive name to mount." 8 39 --title "Messgae count input" 3>&1 1>&2 2>&3)

echo -n "$Mount"

sudo mount /dev/$Mount /mnt/sdb

sudo cp -r /home/pi/sambashare /mnt/sdb/

echo -n "mounted on /mnt/sdb/ \n"

echo -n "Starting samba server to share external drive data \n"

sleep 2

sudo service smbd stop

sudo nano /etc/samba/smb.conf

sudo service smbd restart

username=$(whiptail --inputbox "Enter the username for samba server." 8 39 --title "Input Username for Samba Server" 3>&1 1>&2 2>&3)

sudo smbpasswd -a $username






#!/bin/bash
rm Logger_default.txt

user[0]=mawoznia
user[1]=mnurzyns
user[2]=andrzej
user[3]=zbyszek
user[4]=kamil

#RUN_MESSENGER=/home/mawoznia/marcin/MessengerOnFileForLinux/MessengerOnFileForLinux/build/bin/./messenger_binary
RUN_MESSENGER=$2

MAX_USER_COUNT=0
if [ $1 -gt 5 ] ; then
    MAX_USER_COUNT=5
else
    MAX_USER_COUNT=$1
fi

for (( i=0; $i < $MAX_USER_COUNT; i++ )) ; do
    new_username=${user[$i]}
    gnome-terminal -e "bash -c \"USER=$new_username; $RUN_MESSENGER; exec bash\""
done

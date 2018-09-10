#!/bin/bash

bash clear_enviroment.sh

cd /home
cd $USER
mkdir messenger
chmod 777 messenger

cd /var/tmp
mkdir messenger
chmod 777 messenger
cd messenger
mkdir chats invitations configuration instalation TEST
chmod 777 *
cd configuration
touch LOGGED REGISTERED
chmod 777 *



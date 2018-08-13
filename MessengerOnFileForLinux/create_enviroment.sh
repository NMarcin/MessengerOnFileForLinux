#!/bin/bash

bash clear_enviroment.sh

cd /home
cd $USER
mkdir messenger
chmod 777 messenger

cd /home
sudo mkdir messenger
sudo chmod 777 messenger
cd messenger
sudo mkdir chats invitations configuration instalation TEST
sudo chmod 777 *
cd configuration
sudo touch LOGGED REGISTERED
sudo chmod 777 *



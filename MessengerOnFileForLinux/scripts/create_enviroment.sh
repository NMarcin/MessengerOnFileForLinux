#!/bin/bash

cd /home
cd $USER
mkdir -p messenger
chmod 1777 messenger

cd /var/tmp
mkdir -p messenger
chmod 1777 messenger
cd messenger
mkdir -p chats invitations configuration instalation TEST
chmod 777 *
cd configuration
touch LOGGED REGISTERED
chmod 1777 *



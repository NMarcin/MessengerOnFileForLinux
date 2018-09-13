#!/bin/bash

cd /home
cd $USER
mkdir messenger
chmod 1777 messenger

cd /var/tmp
mkdir messenger
chmod 1777 messenger
cd messenger
mkdir chats invitations configuration instalation TEST
chmod 1777 *
cd configuration
touch LOGGED REGISTERED
chmod 1777 *



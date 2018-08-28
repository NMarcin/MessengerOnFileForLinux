rm /home/mawoznia/marcin/MessengerOnFileForLinux/MessengerOnFileForLinux/build/bin/./messenger_binary
cd /home/mawoznia/marcin/MessengerOnFileForLinux/MessengerOnFileForLinux/build && make
cd /home/mawoznia/marcin/MessengerOnFileForLinux/MessengerOnFileForLinux/

bash create_enviroment.sh
bash run_messenger.sh $1

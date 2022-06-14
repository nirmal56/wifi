# wifi
wifi connect/disconnect event capture

day-1:

there are three task

Wifi connect-disconnect event capture on linux machine (Nirmal)
skill: Event programming, Function pointer, Call back function, kernel event, External API utilize

git repository dependency clearance for linux service project (Anisha)
skill: git knowledge, third party library, linux shell scripting, devops

Linux process profile monitor for memory and CPU (Valgrind) (Mayank)
skill: stress testing, memory leak observation, process optimization, memory optimization



Nirmal:
https://cgit.freedesktop.org/NetworkManager/NetworkManager/tree/examples/C/glib/add-connection-libnm.c





Day-2

quick-start: https://googleapis.github.io/google-cloud-cpp/google/cloud/networkmanagement/quickstart/
networkmanger leaves ubuntu wihtout internet: https://askubuntu.com/questions/841666/installing-networkmanager-leaves-ubuntu-14-04-without-internetick
network manager git link: https://wiki.gnome.org/Projects/NetworkManager
how to install networkmanager in ubuntu : https://askubuntu.com/questions/195499/how-to-install-networkmanager-0-9-0-tar-bz2-package-on-10-10


FOR INSTALLATION: 
THIS WORKED:  https://computingforgeeks.com/install-and-use-networkmanager-nmcli-on-ubuntu-debian/


sudo apt-get update && sudo apt-get upgrade
sudo apt-get install network-manager
sudo systemctl start NetworkManager.service
sudo systemctl enable NetworkManager.service


nmcli connection show
nmcli connection show "Wired connection 1"

working till now





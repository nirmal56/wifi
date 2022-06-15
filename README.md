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


sudo apt install libsystemd-dev  
fixed inclusion of
#include <gio/gio.h>
#include <nm-dbus-interface.h>
NOT WORKED





WORKED: sudo apt install libnm-dev



examples study:
https://fossies.org/linux/misc/NetworkManager-1.38.0.tar.xz/NetworkManager-1.38.0/examples/C/glib/get-ap-info-libnm.c?m=t
Working code gives gives available networks: https://cgit.freedesktop.org/NetworkManager/NetworkManager/tree/examples/C/glib/get-active-connections-gdbus.c


REFERENCE MANUALS:
https://developer-old.gnome.org/libnm/stable/
https://developer-old.gnome.org/libnm/stable/usage.html





DAY3:

enum NMConnectivityState:

NM_CONNECTIVITY_UNKNOWN

Network connectivity is unknown. This means the connectivity checks are disabled (e.g. on server installations) or has not run yet. The graphical shell should assume the Internet connection might be available and not present a captive portal window.

 
NM_CONNECTIVITY_NONE

The host is not connected to any network. There's no active connection that contains a default route to the internet and thus it makes no sense to even attempt a connectivity check. The graphical shell should use this state to indicate the network connection is unavailable.

 
NM_CONNECTIVITY_PORTAL

The Internet connection is hijacked by a captive portal gateway. The graphical shell may open a sandboxed web browser window (because the captive portals typically attempt a man-in-the-middle attacks against the https connections) for the purpose of authenticating to a gateway and retrigger the connectivity check with CheckConnectivity() when the browser window is dismissed.

 
NM_CONNECTIVITY_LIMITED

The host is connected to a network, does not appear to be able to reach the full Internet, but a captive portal has not been detected.

 
NM_CONNECTIVITY_FULL

The host is connected to a network, and appears to be able to reach the full Internet.
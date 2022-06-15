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

enum NMState
NMState values indicate the current overall networking state.

Values
NM_STATE_UNKNOWN = 0             networking state is unknown

 
NM_STATE_ASLEEP = 10             networking is not enabled

 
NM_STATE_DISCONNECTED = 20           there is no active network connection

 
NM_STATE_DISCONNECTING = 30          network connections are being cleaned up

 
NM_STATE_CONNECTING = 40             a network connection is being started

 
NM_STATE_CONNECTED_LOCAL = 50            there is only local IPv4 and/or IPv6 connectivity

 
NM_STATE_CONNECTED_SITE = 60             there is only site-wide IPv4 and/or IPv6 connectivity

 
NM_STATE_CONNECTED_GLOBAL = 70           there is global IPv4 and/or IPv6 Internet connectivity

 
GnetworkMonitor:https://www.freedesktop.org/software/gstreamer-sdk/data/docs/2012.5/gio/GNetworkMonitor.html

GDBusProxy *        g_dbus_proxy_new_for_bus_sync       (GBusType bus_type,
                                                         GDBusProxyFlags flags,
                                                         GDBusInterfaceInfo *info,
                                                         const gchar *name,
                                                         const gchar *object_path,
                                                         const gchar *interface_name,
                                                         GCancellable *cancellable,
                                                         GError **error);
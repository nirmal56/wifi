#include <glib.h>
#include <NetworkManager.h>
// #include <nmcli.h>

int main (int argc, char *argv[])
{
	NMClient *client;
    const char * mystruct;
    NMDnsEntry *entry;

	client = nm_client_new (NULL, NULL);
	if (client)
		g_print ("NetworkManager version: %s\n", nm_client_get_version (client));
        mystruct = nm_dns_entry_get_domains (&entry);
}
#include <glib.h>
#include <NetworkManager.h>

int main (int argc, char *argv[])
{
	NMClient *client;

	client = nm_client_new (NULL, NULL);
	if (client)
		g_print ("NetworkManager version: %s\n", nm_client_get_version (client));
}
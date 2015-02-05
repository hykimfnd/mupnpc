/******************************************************************
*
*	CyberNet for C
*
*	Copyright (C) Satoshi Konno 2005
*
*       Copyright (C) 2006 Nokia Corporation. All rights reserved.
*
*       This is licensed under BSD-style license,
*       see file COPYING.
*
*	File: cinterface.cpp
*
*	Revision:
*
*	02/09/05
*		- first revision
*	02/09/05
*		- Added mupnp_net_interface_setnetmask() and mupnp_net_interface_getnetmask().
*	09/12/07
*		- Added the following functions to get MAC address.
*		  mupnp_net_interface_setmacaddress(), mupnp_net_interface_getmacaddress()
*
******************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <mupnp/net/interface.h>
#include <mupnp/util/log.h>
#include <string.h>

/****************************************
* mupnp_net_interface_new
****************************************/

CgNetworkInterface *mupnp_net_interface_new()
{
	CgNetworkInterface *netIf;

	mupnp_log_debug_l4("Entering...\n");

	netIf = (CgNetworkInterface *)malloc(sizeof(CgNetworkInterface));

	if ( NULL != netIf )
	{
		mupnp_list_node_init((CgList *)netIf);
		netIf->name = mupnp_string_new();
		netIf->ipaddr = mupnp_string_new();
		netIf->netmask = mupnp_string_new();
		mupnp_net_interface_setindex(netIf, 0);
		memset(netIf->macaddr, 0, (size_t)CG_NET_MACADDR_SIZE);
	}
	
	mupnp_log_debug_l4("Leaving...\n");

	return netIf;
}

/****************************************
* mupnp_net_interface_delete
****************************************/

void mupnp_net_interface_delete(CgNetworkInterface *netIf)
{
	mupnp_log_debug_l4("Entering...\n");

	mupnp_list_remove((CgList *)netIf);
	mupnp_string_delete(netIf->name);
	mupnp_string_delete(netIf->ipaddr);
	mupnp_string_delete(netIf->netmask);

	mupnp_log_debug_l4("Leaving...\n");

	free(netIf);
}

/****************************************
* mupnp_net_interface_getany
****************************************/

CgNetworkInterface *mupnp_net_interface_getany()
{
	CgNetworkInterface *netIf;

	mupnp_log_debug_l4("Entering...\n");

	netIf = mupnp_net_interface_new();
	/* It would be more approriate to use INADDR_ANY, but this will do */
	mupnp_net_interface_setname(netIf, "INADDR_ANY");
	mupnp_net_interface_setaddress(netIf, "0.0.0.0");
	
	mupnp_log_debug_l4("Leaving...\n");

	return netIf;
}

/****************************************
* mupnp_net_interface_setname
****************************************/

void mupnp_net_interface_setname(CgNetworkInterface *netIf, char *name)
{
	mupnp_log_debug_l4("Entering...\n");

	mupnp_string_setvalue(netIf->name, name);

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_net_interface_getname
****************************************/

char *mupnp_net_interface_getname(CgNetworkInterface *netIf)
{
	mupnp_log_debug_l4("Entering...\n");

	return mupnp_string_getvalue(netIf->name);

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_net_interface_setaddress
****************************************/

void mupnp_net_interface_setaddress(CgNetworkInterface *netIf, char *value)
{
	mupnp_log_debug_l4("Entering...\n");

	mupnp_string_setvalue(netIf->ipaddr, value);

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_net_interface_getaddress
****************************************/

char *mupnp_net_interface_getaddress(CgNetworkInterface *netIf)
{
	mupnp_log_debug_l4("Entering...\n");

	return mupnp_string_getvalue(netIf->ipaddr);

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_net_interface_setnetmask
****************************************/

void mupnp_net_interface_setnetmask(CgNetworkInterface *netIf, char *value)
{
	mupnp_log_debug_l4("Entering...\n");

	mupnp_string_setvalue(netIf->netmask, value);

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_net_interface_getnetmask
****************************************/

char *mupnp_net_interface_getnetmask(CgNetworkInterface *netIf)
{
	mupnp_log_debug_l4("Entering...\n");

	return mupnp_string_getvalue(netIf->netmask);

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_net_interface_cmp
****************************************/

int mupnp_net_interface_cmp(CgNetworkInterface *netIfA, 
			 CgNetworkInterface *netIfB)
{
	mupnp_log_debug_l4("Entering...\n");

	if (netIfA == NULL && netIfB == NULL) return 0;
	if (netIfA == NULL && netIfB != NULL) return 1;
	if (netIfA != NULL && netIfB == NULL) return -1;
	
	return mupnp_strcmp(mupnp_net_interface_getaddress(netIfA), 
			 mupnp_net_interface_getaddress(netIfB));

	mupnp_log_debug_l4("Leaving...\n");
}
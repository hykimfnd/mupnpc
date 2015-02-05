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
*	File: cssdp_notify_server_list.c
*
*	Revision:
*
*	05/31/05
*		- first revision
*
*	10/31/05
*		- Changed "continue;" to "return FALSE;" in serverlist_open
*		  to indicate that port allocation was unsuccessful
*	12/14/05
*		- Fixed memory leak situation, which was introduced by 
*		  the previous patch
*	02/13/06 Theo Beisch
*		- mupnp_upnp_ssdpresponse_serverlist_open now returns true if
*		  at least a single open was successfull (WINCE support)
*
******************************************************************/

#include <mupnp/ssdp/ssdp_server.h>
#include <mupnp/net/interface.h>
#include <mupnp/util/log.h>

/****************************************
* CG_UPNP_NOUSE_CONTROLPOINT (Begin)
****************************************/

#if !defined(CG_UPNP_NOUSE_CONTROLPOINT)

/****************************************
* mupnp_upnp_ssdpresponse_serverlist_new
****************************************/

CgUpnpSSDPResponseServerList *mupnp_upnp_ssdpresponse_serverlist_new()
{
	CgUpnpSSDPResponseServerList *ssdpServerList;

	mupnp_log_debug_l4("Entering...\n");

	ssdpServerList = (CgUpnpSSDPResponseServerList *)malloc(sizeof(CgUpnpSSDPResponseServerList));

	if  ( NULL != ssdpServerList )
	{
		mupnp_list_header_init((CgList *)ssdpServerList);
		
		ssdpServerList->httpuSock = NULL;
		ssdpServerList->recvThread = NULL;
		ssdpServerList->listener = NULL;
	}
	
	return ssdpServerList;

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_upnp_ssdpresponse_serverlist_delete
****************************************/

void mupnp_upnp_ssdpresponse_serverlist_delete(CgUpnpSSDPResponseServerList *ssdpServerList)
{
	mupnp_log_debug_l4("Entering...\n");

	mupnp_upnp_ssdpresponse_serverlist_clear(ssdpServerList);
	
	free(ssdpServerList);

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_upnp_ssdpresponse_serverlist_open
****************************************/

BOOL mupnp_upnp_ssdpresponse_serverlist_open(CgUpnpSSDPResponseServerList *ssdpServerList, int bindPort)
{
	CgNetworkInterfaceList *netIfList;
	CgNetworkInterface *netIf;
	CgUpnpSSDPResponseServer *ssdpServer;
	char *bindAddr;
	BOOL result = FALSE;	

	mupnp_log_debug_l4("Entering...\n");

	netIfList = mupnp_net_interfacelist_new();
#ifndef CG_NET_USE_ANYADDR
	mupnp_net_gethostinterfaces(netIfList);
#else
	netIf = mupnp_net_interface_getany();
	mupnp_net_interfacelist_add(netIfList, netIf);
#endif
	for (netIf = mupnp_net_interfacelist_gets(netIfList); netIf; netIf = mupnp_net_interface_next(netIf)) {
		bindAddr = mupnp_net_interface_getaddress(netIf);
		if (mupnp_strlen(bindAddr) <= 0)
			continue;
		ssdpServer = mupnp_upnp_ssdpresponse_server_new();
		if (mupnp_upnp_ssdpresponse_server_open(ssdpServer, bindPort, bindAddr) == FALSE) {
			mupnp_upnp_ssdpresponse_server_delete(ssdpServer);
			continue;
		}
		mupnp_upnp_ssdpresponse_serverlist_add(ssdpServerList, ssdpServer);
		result = TRUE;
	}

	if (result == FALSE) mupnp_upnp_ssdpresponse_serverlist_clear(ssdpServerList);

	mupnp_net_interfacelist_delete(netIfList);

	return result;	
}

/****************************************
* mupnp_upnp_ssdpresponse_serverlist_close
****************************************/

BOOL mupnp_upnp_ssdpresponse_serverlist_close(CgUpnpSSDPResponseServerList *ssdpServerList)
{
	CgUpnpSSDPResponseServer *ssdpServer;

	mupnp_log_debug_l4("Entering...\n");
	
	for (ssdpServer = mupnp_upnp_ssdpresponse_serverlist_gets(ssdpServerList); ssdpServer != NULL; ssdpServer = mupnp_upnp_ssdpresponse_server_next(ssdpServer))
		mupnp_upnp_ssdpresponse_server_close(ssdpServer);

	return TRUE;

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_upnp_ssdpresponse_serverlist_start
****************************************/

BOOL mupnp_upnp_ssdpresponse_serverlist_start(CgUpnpSSDPResponseServerList *ssdpServerList)
{
	CgUpnpSSDPResponseServer *ssdpServer;
	
	mupnp_log_debug_l4("Entering...\n");

	for (ssdpServer = mupnp_upnp_ssdpresponse_serverlist_gets(ssdpServerList); ssdpServer != NULL; ssdpServer = mupnp_upnp_ssdpresponse_server_next(ssdpServer))
		mupnp_upnp_ssdpresponse_server_start(ssdpServer);
	
	return TRUE;

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_upnp_ssdpresponse_serverlist_stop
****************************************/

BOOL mupnp_upnp_ssdpresponse_serverlist_stop(CgUpnpSSDPResponseServerList *ssdpServerList)
{
	CgUpnpSSDPResponseServer *ssdpServer;
	
	mupnp_log_debug_l4("Entering...\n");

	for (ssdpServer = mupnp_upnp_ssdpresponse_serverlist_gets(ssdpServerList); ssdpServer != NULL; ssdpServer = mupnp_upnp_ssdpresponse_server_next(ssdpServer))
		mupnp_upnp_ssdpresponse_server_stop(ssdpServer);
		
	return TRUE;

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_upnp_ssdpresponse_serverlist_setlistener
****************************************/

void mupnp_upnp_ssdpresponse_serverlist_setlistener(CgUpnpSSDPResponseServerList *ssdpServerList, CG_UPNP_SSDP_LISTNER listener)
{
	CgUpnpSSDPResponseServer *ssdpServer;
	
	mupnp_log_debug_l4("Entering...\n");

	for (ssdpServer = mupnp_upnp_ssdpresponse_serverlist_gets(ssdpServerList); ssdpServer != NULL; ssdpServer = mupnp_upnp_ssdpresponse_server_next(ssdpServer))
		mupnp_upnp_ssdpresponse_server_setlistener(ssdpServer, listener);

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_upnp_ssdpresponse_serverlist_setuserdata
****************************************/

void mupnp_upnp_ssdpresponse_serverlist_setuserdata(CgUpnpSSDPResponseServerList *ssdpServerList, void *data)
{
	CgUpnpSSDPResponseServer *ssdpServer;
	
	mupnp_log_debug_l4("Entering...\n");

	for (ssdpServer = mupnp_upnp_ssdpresponse_serverlist_gets(ssdpServerList); ssdpServer != NULL; ssdpServer = mupnp_upnp_ssdpresponse_server_next(ssdpServer))
		mupnp_upnp_ssdpresponse_server_setuserdata(ssdpServer, data);

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_upnp_ssdpresponse_serverlist_post
****************************************/

BOOL mupnp_upnp_ssdpresponse_serverlist_post(CgUpnpSSDPResponseServerList *ssdpServerList, CgUpnpSSDPRequest *ssdpReq)
{
	CgUpnpSSDPResponseServer *ssdpServer;
	BOOL success = TRUE;
	
	mupnp_log_debug_l4("Entering...\n");

	for (ssdpServer = mupnp_upnp_ssdpresponse_serverlist_gets(ssdpServerList); ssdpServer != NULL; ssdpServer = mupnp_upnp_ssdpresponse_server_next(ssdpServer))
		success &= mupnp_upnp_ssdpresponse_server_post(ssdpServer, ssdpReq);
		
	return success;

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* CG_UPNP_NOUSE_CONTROLPOINT (End)
****************************************/

#endif
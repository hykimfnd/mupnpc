/************************************************************
*
*	CyberLink for C
*
*	Copyright (C) Satoshi Konno 2005
*
*	File: cavtransport_service.c
*
*	Revision:
*		2009/06/11
*        - first release.
*
************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <cybergarage/upnp/std/av/cmediarenderer.h>

/****************************************
* Service Description (AVTransport)
****************************************/

static char *CG_UPNPAV_DMR_AVTRANSPORT_SERVICE_DESCRIPTION = 
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
"<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\">\n"
"   <specVersion>\n"
"      <major>1</major>\n"
"      <minor>0</minor>\n"
"   </specVersion>\n"
"     <serviceStateTable> \n"
"         <stateVariable> \n"
"             <name>TransportState</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"             <allowedValueList> \n"
"                 <allowedValue>STOPPED</allowedValue> \n"
"                 <allowedValue>PLAYING</allowedValue> \n"
"             </allowedValueList> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>TransportStatus</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"             <allowedValueList> \n"
"                 <allowedValue>OK</allowedValue> \n"
"                 <allowedValue>ERROR_OCCURRED</allowedValue>            \n"
"             </allowedValueList> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>PlaybackStorageMedium</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"         </stateVariable> \n"
" 	 <stateVariable> \n"
"             <name>RecordStorageMedium</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"               </stateVariable> \n"
"         <stateVariable> \n"
"             <name>PossiblePlaybackStorageMedia</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>PossibleRecordStorageMedia</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>CurrentPlayMode</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"             <allowedValueList> \n"
"                 <allowedValue>NORMAL</allowedValue> \n"
"             </allowedValueList> \n"
"             <defaultValue>NORMAL</defaultValue> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>TransportPlaySpeed</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
" 	<allowedValueList> \n"
"                 <allowedValue>1</allowedValue> \n"
"             </allowedValueList> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <name>RecordMediumWriteStatus </name> \n"
"             <dataType>string</dataType> \n"
"          </stateVariable> \n"
"         <stateVariable> \n"
"             <name>CurrentRecordQualityMode</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"           </stateVariable> \n"
"         <stateVariable> \n"
"             <name>PossibleRecordQualityModes</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>NumberOfTracks</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>ui4</dataType> \n"
" 		<allowedValueRange> \n"
" 			<minimum>0</minimum> \n"
" 		</allowedValueRange> \n"
"          </stateVariable> \n"
"         <stateVariable> \n"
"             <name>CurrentTrack</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>ui4</dataType> \n"
" 		<allowedValueRange> \n"
" 			<minimum>0</minimum> \n"
" 			<step>1</step> \n"
" 		</allowedValueRange> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>CurrentTrackDuration</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"         </stateVariable> \n"
" 	  <stateVariable> \n"
"             <name>CurrentMediaDuration</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>CurrentTrackMetaData</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>CurrentTrackURI</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>AVTransportURI</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>AVTransportURIMetaData</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>NextAVTransportURI</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>NextAVTransportURIMetaData</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>RelativeTimePosition</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>AbsoluteTimePosition</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>RelativeCounterPosition</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>i4</dataType> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>AbsoluteCounterPosition</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>i4</dataType> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
" 		<Optional/> \n"
"             <name>CurrentTransportActions</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>LastChange</name> \n"
"             <sendEventsAttribute>yes</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>A_ARG_TYPE_SeekMode</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"             <allowedValueList> \n"
"                  <allowedValue>TRACK_NR</allowedValue> \n"
"             </allowedValueList> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>A_ARG_TYPE_SeekTarget</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>string</dataType> \n"
"         </stateVariable> \n"
"         <stateVariable> \n"
"             <name>A_ARG_TYPE_InstanceID</name> \n"
"             <sendEventsAttribute>no</sendEventsAttribute> \n"
"             <dataType>ui4</dataType> \n"
"         </stateVariable> \n"
"     </serviceStateTable> \n"
"     <actionList> \n"
"         <action> \n"
"             <name>SetAVTransportURI</name> \n"
"             <argumentList> \n"
"                 <argument> \n"
"                     <name>InstanceID</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_InstanceID</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>CurrentURI</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>AVTransportURI</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>CurrentURIMetaData</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>AVTransportURIMetaData</relatedStateVariable> \n"
"                 </argument> \n"
"             </argumentList> \n"
"         </action> \n"
"         <action>	<Optional/> \n"
"             <name>SetNextAVTransportURI</name> \n"
"             <argumentList> \n"
"                 <argument> \n"
"                     <name>InstanceID</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_InstanceID</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>NextURI</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>NextAVTransportURI</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>NextURIMetaData</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>NextAVTransportURIMetaData</relatedStateVariable> \n"
"                 </argument> \n"
"             </argumentList> \n"
"         </action> \n"
"         <action> \n"
"             <name>GetMediaInfo</name> \n"
"             <argumentList> \n"
"                 <argument> \n"
"                     <name>InstanceID</name> \n"
"                     <direction>in</direction>\n"
"                 <relatedStateVariable>A_ARG_TYPE_InstanceID</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>NrTracks</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>NumberOfTracks</relatedStateVariable> \n"
"                 </argument> \n"
"                <argument> \n"
"                     <name>MediaDuration</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>CurrentMediaDuration</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>CurrentURI</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>AVTransportURI</relatedStateVariable> \n"
"                 </argument> \n"
" 		    <argument> \n"
"                     <name>CurrentURIMetaData</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>AVTransportURIMetaData</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>NextURI</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>NextAVTransportURI</relatedStateVariable> \n"
"                 </argument> \n"
" 		    <argument> \n"
"                     <name>NextURIMetaData</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>NextAVTransportURIMetaData</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>PlayMedium</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>PlaybackStorageMedium</relatedStateVariable> \n"
"                 </argument> \n"
" <argument> \n"
"                     <name>RecordMedium</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>RecordStorageMedium</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>WriteStatus</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>RecordMediumWriteStatus </relatedStateVariable> \n"
"                 </argument> \n"
"             </argumentList> \n"
"         </action> \n"
"         <action> \n"
"             <name>GetTransportInfo</name> \n"
"             <argumentList> \n"
"                 <argument> \n"
"                     <name>InstanceID</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_InstanceID</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>CurrentTransportState</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>TransportState</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>CurrentTransportStatus</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>TransportStatus</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>CurrentSpeed</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>TransportPlaySpeed</relatedStateVariable> \n"
"                 </argument> \n"
"             </argumentList> \n"
"         </action> \n"
"         <action> \n"
"             <name>GetPositionInfo</name> \n"
"             <argumentList> \n"
"                 <argument> \n"
"                     <name>InstanceID</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_InstanceID</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>Track</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>CurrentTrack</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>TrackDuration</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>CurrentTrackDuration</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>TrackMetaData</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>CurrentTrackMetaData</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>TrackURI</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>CurrentTrackURI</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>RelTime</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>RelativeTimePosition</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>AbsTime</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>AbsoluteTimePosition</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>RelCount</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>RelativeCounterPosition</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>AbsCount</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>AbsoluteCounterPosition</relatedStateVariable> \n"
"                 </argument> \n"
"             </argumentList> \n"
"         </action> \n"
"         <action> \n"
"             <name>GetDeviceCapabilities</name> \n"
"             <argumentList> \n"
"                 <argument> \n"
"                     <name>InstanceID</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_InstanceID</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>PlayMedia</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>PossiblePlaybackStorageMedia</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>RecMedia</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>PossibleRecordStorageMedia</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>RecQualityModes</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>PossibleRecordQualityModes</relatedStateVariable> \n"
"                 </argument> \n"
"             </argumentList> \n"
"         </action> \n"
"         <action> \n"
"             <name>GetTransportSettings</name> \n"
"             <argumentList> \n"
"                 <argument> \n"
"                     <name>InstanceID</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_InstanceID</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>PlayMode</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>CurrentPlayMode</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>RecQualityMode</name> \n"
"                     <direction>out</direction>\n"
"                 <relatedStateVariable>CurrentRecordQualityMode</relatedStateVariable> \n"
"                 </argument> \n"
"             </argumentList> \n"
"         </action> \n"
"         <action> \n"
"             <name>Stop</name> \n"
"             <argumentList> \n"
"                 <argument> \n"
"                     <name>InstanceID</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_InstanceID</relatedStateVariable> \n"
"                 </argument> \n"
"             </argumentList> \n"
"         </action> \n"
"         <action> \n"
"             <name>Play</name> \n"
"             <argumentList> \n"
"                 <argument> \n"
"                     <name>InstanceID</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_InstanceID</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>Speed</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>TransportPlaySpeed</relatedStateVariable> \n"
"                 </argument> \n"
"             </argumentList> \n"
"         </action> \n"
"         <action>	<Optional/> \n"
"             <name>Pause</name> \n"
"             <argumentList> \n"
"                 <argument> \n"
"                     <name>InstanceID</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_InstanceID</relatedStateVariable> \n"
"                 </argument> \n"
"             </argumentList> \n"
"         </action> \n"
"         <action>	<Optional/> \n"
"             <name>Record</name> \n"
"             <argumentList> \n"
"                 <argument> \n"
"                     <name>InstanceID</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_InstanceID</relatedStateVariable> \n"
"                 </argument> \n"
"             </argumentList> \n"
"         </action> \n"
"         <action> \n"
"             <name>Seek</name> \n"
"             <argumentList> \n"
"                 <argument> \n"
"                     <name>InstanceID</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_InstanceID</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>Unit</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_SeekMode</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>Target</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_SeekTarget</relatedStateVariable> \n"
"                 </argument> \n"
"             </argumentList> \n"
"         </action> \n"
"         <action> \n"
"             <name>Next</name> \n"
"             <argumentList> \n"
"                 <argument> \n"
"                     <name>InstanceID</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_InstanceID</relatedStateVariable> \n"
"                 </argument> \n"
"             </argumentList> \n"
"         </action> \n"
"         <action> \n"
"             <name>Previous</name> \n"
"             <argumentList> \n"
"                 <argument> \n"
"                     <name>InstanceID</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_InstanceID</relatedStateVariable> \n"
"                 </argument> \n"
"             </argumentList> \n"
"         </action> \n"
"         <action>	<Optional/> \n"
"             <name>SetPlayMode</name> \n"
"             <argumentList> \n"
"                 <argument> \n"
"                     <name>InstanceID</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_InstanceID</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>NewPlayMode</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>CurrentPlayMode</relatedStateVariable> \n"
"                 </argument> \n"
"             </argumentList> \n"
"         </action> \n"
"         <action>	<Optional/> \n"
"             <name>SetRecordQualityMode</name> \n"
"             <argumentList> \n"
"                 <argument> \n"
"                     <name>InstanceID</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_InstanceID</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>NewRecordQualityMode</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>CurrentRecordQualityMode</relatedStateVariable> \n"
"                 </argument> \n"
"             </argumentList> \n"
"         </action> \n"
"         <action>	<Optional/> \n"
"             <name>GetCurrentTransportActions</name> \n"
"             <argumentList> \n"
"                 <argument> \n"
"                     <name>InstanceID</name> \n"
"                     <direction>in</direction>\n"
"                    <relatedStateVariable>A_ARG_TYPE_InstanceID</relatedStateVariable> \n"
"                 </argument> \n"
"                 <argument> \n"
"                     <name>Actions</name> \n"
"                     <direction>out</direction>\n"
"                    <relatedStateVariable>CurrentTransportActions</relatedStateVariable> \n"
"                 </argument> \n"
"             </argumentList> \n"
"         </action> \n"
"     </actionList> \n"
" </scpd>\n";

/****************************************
* cg_upnpav_dmr_avtransport_actionreceived
****************************************/

BOOL cg_upnpav_dmr_avtransport_actionreceived(CgUpnpAction *action)
{
	CgUpnpAvRenderer *dmr;
	CgUpnpDevice *dev;
	char *actionName;
	CgUpnpArgument *arg;

	actionName = cg_upnp_action_getname(action);
	if (cg_strlen(actionName) <= 0)
		return FALSE;

	dev = (CgUpnpDevice *)cg_upnp_service_getdevice(cg_upnp_action_getservice(action));
	if (!dev) 
		return FALSE;

	dmr = (CgUpnpAvRenderer *)cg_upnp_device_getuserdata(dev);
	if (!dmr)
		return FALSE;

	return FALSE;
}

/****************************************
 * cg_upnpav_dmr_avtransport_queryreceived
 ****************************************/

BOOL cg_upnpav_dmr_avtransport_queryreceived(CgUpnpStateVariable *statVar)
{
	return FALSE;
}

/****************************************
* cg_upnpav_dmr_avtransport_init
****************************************/

BOOL cg_upnpav_dmr_avtransport_init(CgUpnpAvRenderer *dmr)
{
	CgUpnpDevice *dev;
	CgUpnpService *service;
	CgUpnpAction *action;

	dev = cg_upnpav_dmr_getdevice(dmr);
	if (!dev)
		return FALSE;

	service = cg_upnp_device_getservicebytype(dev, CG_UPNPAV_DMR_AVTRANSPORT_SERVICE_TYPE);
	if (!service)
		return FALSE;
	
	if (cg_upnp_service_parsedescription(service, CG_UPNPAV_DMR_AVTRANSPORT_SERVICE_DESCRIPTION, cg_strlen(CG_UPNPAV_DMR_AVTRANSPORT_SERVICE_DESCRIPTION)) == FALSE)
		return FALSE;

	cg_upnp_service_setuserdata(service, dmr);
	for (action=cg_upnp_service_getactions(service); action; action=cg_upnp_action_next(action))
		cg_upnp_action_setuserdata(action, dmr);

	return TRUE;
}
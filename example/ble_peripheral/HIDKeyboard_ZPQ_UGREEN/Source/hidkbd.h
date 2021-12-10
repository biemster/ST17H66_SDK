/**************************************************************************************************
*******
**************************************************************************************************/

/******************************************************************************

 *****************************************************************************/

#ifndef HIDEMUKBD_H
#define HIDEMUKBD_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
 * CONSTANTS
 */

// Task Events
#define START_DEVICE_EVT								0x0001
#define HID_LATENCY_TURNOFF_EVT							0x4000
/*********************************************************************
 * MACROS
 */

// Send HID Value
#define		PLAY_KEY_RELEASE	0x00
#define		PLAY_AND_PAUSE		0x01
#define		PLAY_MODE_SHIFT		0x02		//	unlock screen
#define		PLAY_VIEW_SHIFT		0x04		//	change camera
#define		PLAY_PREV_TRACK		0x08
#define		PLAY_VOICE_DOWN		0x10
#define		PLAY_VOICE_UP		0x20
#define		PLAY_AC_ZOOMIN		0x40
#define		PLAY_AC_ZOOMOUT		0x80


// MAC defines
#define	MAC_DATA_LENGTH					6

typedef struct 
{
	uint8 len;
	uint8 name_str[16];
}lc_selfie_name_info;

/*********************************************************************
 * FUNCTIONS
 */
  
/*********************************************************************
 * GLOBAL VARIABLES
 */

extern uint8 hidKbdTaskId;
extern uint8 g_instant_cnt;

/*
 * Task Initialization for the BLE Application
 */
extern void HidKbd_Init( uint8 task_id );

/*
 * Task Event Processor for the BLE Application
 */
extern	uint16	HidKbd_ProcessEvent				( uint8 task_id, uint16 events );
extern	uint8	hidKbdSendVoiceCMDtReport	( uint8 keycode );
extern	void	hidCCSendReportKey				( uint8 cmd, bool keyPressed);
extern	void 	hidCCSendReport					( uint8 cmd, bool keyPressed, uint8 keyRepeated );
/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /*HIDEMUKBD_H */

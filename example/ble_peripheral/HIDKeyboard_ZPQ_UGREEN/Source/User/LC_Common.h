/**
*	@file	LC_Common.h
*	@date	10/20/2020
*	@version	1.0.1
*
*/

/*!
 * 	@defgroup	LC_Common
 *	@brief
 *	@{*/
#ifndef		LC_COMMON_H_
#define		LC_COMMON_H_
/*------------------------------------------------------------------*/
/*						C++ guard macro								*/
/*------------------------------------------------------------------*/
#ifdef	__cplusplus
	 extern  "C" {
#endif
/*------------------------------------------------------------------*/
/* 				 		head files include 							*/
/*------------------------------------------------------------------*/

#include "att.h"
#include "bcomdef.h"
#include "gapbondmgr.h"
#include "gapgattserver.h"
#include "gatt.h"
#include "gatt_uuid.h"
#include "gattservapp.h"
#include "global_config.h"
#include "hci.h"
#include "hci_tl.h"
#include "linkdb.h"
#include "ll.h"
#include "ll_def.h"
#include "ll_hw_drv.h"
#include "OSAL.h"
#include "OSAL_PwrMgr.h"
#include "ota_app_service.h"
#include "peripheral.h"
#include "pwm.h"
#include "pwrmgr.h"
#include "rf_phy_driver.h"
#include "Hidkbd.h"
#include "battservice.h"
#include "hiddev.h"
#include "osal_snv.h"
#include "flash.h"
#include "gpio.h"

//#include "simpleBLEPeripheral.h"
//#include "sbpProfile_ota.h"
#include "adc.h"
/*------------------------------------------------------------------*/
/*						Pins definitions							*/
/*------------------------------------------------------------------*/
#define		MY_GPIO_NAME_OP1		P34
#define		MY_GPIO_NAME_OP2		P2
#define		MY_GPIO_NAME_OP3		P7
/*------------------------------------------------------------------*/
/*						MACROS										*/
/*------------------------------------------------------------------*/
//	Enable Device Suspend
#define		LC_ZPQ_SUSPEND_ENABLE		1
//	Reserve date in FS
#define		SNV_DEV_SOFT_RESET			0xF1
//	Timeout in each mode
#define		LC_DEV_TIMER_POWEROFF		(10*10 + 1)
#define		LC_DEV_TIMER_SUSPEND		(10*10 + 1)

/*------------------------------------------------------------------*/
/*						UI Task Events definitions					*/
/*------------------------------------------------------------------*/


/*------------------------------------------------------------------*/
/* 					 	Data structures							 	*/
/*------------------------------------------------------------------*/
typedef uint8_t				u8;
typedef uint16_t			u16;
typedef uint32_t			u32;
typedef signed   char		int8_t;		//!< Signed 8 bit integer
typedef unsigned char		uint8_t;		//!< Unsigned 8 bit integer
typedef signed   short		int16_t;		//!< Signed 16 bit integer
typedef unsigned short		uint16_t;		//!< Unsigned 16 bit integer
typedef signed   int		int32_t;		//!< Signed 32 bit integer
typedef unsigned int		uint32_t;		//!< Unsigned 32 bit integer
typedef signed   char		int8;			//!< Signed 8 bit integer
typedef unsigned char		uint8;			//!< Unsigned 8 bit integer
typedef signed   short		int16;			//!< Signed 16 bit integer
typedef unsigned short		uint16;		//!< Unsigned 16 bit integer
typedef signed   long		int32;			//!< Signed 32 bit integer
typedef unsigned long		uint32;		//!< Unsigned 32 bit integer

typedef		enum	{
	LC_DEV_BLE_DISCONNECTION	=	0,
	LC_DEV_BLE_CONNECTION,
}lc_dev_ble_state;

typedef		enum	{
	State_Off	=	0,
	State_On	=	1,
}lc_state_bool;

typedef		enum	{
	SYSTEM_STANDBY	=	0,
	SYSTEM_WORKING	=	1,
	SYSTEM_SUSPEND	=	2,
}lc_sys_run_t;

typedef	enum
{
	OLD_PHONE	=	0,
	NEW_PHONE	=	1,
}phone_type_t;

typedef struct
{
	uint32			dev_timeout_poweroff_cnt;		//	power off time
	uint32			dev_timeout_suspend_cnt;		//	suspend time
	uint32			dev_adv_change_tick;			//	adv change interval tick in adv state
	uint8			dev_timer_poweroff_flag;		
	uint8			dev_poweron_switch_flag;		//	power on switch exist or not		:1	no switch,	0	
	uint8			dev_power_flag;					//	device working flag				:1	working,		0	power off
	uint8			dev_lowpower_flag;				//	lower power mode flag				:1	
	uint8			dev_ble_con_state;				//	BLE	connection state				:1	connected,	0	disconnected
	uint8			dev_batt_value;					//	device battery pecent
	uint8			dev_adv_ctrl_num;				//	second cnt change adv interval
	uint8			dev_adv_change_flag;			//	change adv interval enable
	uint8			dev_keyconn_enable;				//	enable key notify after connect 1s
	phone_type_t	dev_phone_type;					//	phone type
}lc_dev_sys_param;

/*------------------------------------------------------------------*/
/* 					 external variables							 	*/
/*------------------------------------------------------------------*/
extern		lc_dev_sys_param	LC_Dev_System_Param;
extern		uint8				hidDevTaskId;
/*------------------------------------------------------------------*/
/* 					 User function prototypes					 	*/
/*------------------------------------------------------------------*/
extern	uint32	clock_time_exceed_func			(uint32 ref,		uint32 span_ms	);
extern	void	LC_Common_ProcessOSALMsg	 	(osal_event_hdr_t *pMsg				);
extern	void	Printf_Hex 						(const uint8 *data,	uint16 len		);
extern	void	LC_Timer_Start					(void);
extern	void	LC_Timer_Stop					(void);
extern	void	LC_Data_Push					(uint8 cmd							);

#ifdef	__cplusplus
}
#endif

#endif	/* LC_COMMON_H_ */
/** @}*/

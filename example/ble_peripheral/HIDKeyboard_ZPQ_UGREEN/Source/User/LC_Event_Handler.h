/**
 *	@file		LC_Event_Handler.h
 *	@date		06/19/2021
 *	@version	1.0.0
 */

/*!
 *	@defgroup	LC_Event_Handler
 *	@brief
 *	@{*/

#ifndef		LC_EVENT_HANDLER_H_
#define		LC_EVENT_HANDLER_H_
/*------------------------------------------------------------------*/
/*						C++ guard macro								*/
/*------------------------------------------------------------------*/
#ifdef	__cplusplus
	extern "C"	{
#endif
/*------------------------------------------------------------------*/
/*						head files include 							*/
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
// #include "battservice.h"
#include "hiddev.h"
#include "osal_snv.h"
#include "flash.h"
#include "gpio.h"
#include "adc.h"

/*------------------------------------------------------------------*/
/*						Pins definitions							*/
/*------------------------------------------------------------------*/

/*------------------------------------------------------------------*/
/*						MACROS										*/
/*------------------------------------------------------------------*/

/*------------------------------------------------------------------*/
/*						UI Task Events definitions					*/
/*------------------------------------------------------------------*/

/*------------------------------------------------------------------*/
/*						Data structures								*/
/*------------------------------------------------------------------*/

/*------------------------------------------------------------------*/
/*						external variables							*/
/*------------------------------------------------------------------*/

/*------------------------------------------------------------------*/
/*						User function prototypes					*/
/*------------------------------------------------------------------*/
void	__ATTR_SECTION_SRAM__  __attribute__((used))	LC_RGB_Valeu_Deal		(uint8 evt		);
void	__ATTR_SECTION_SRAM__  __attribute__((used))	LC_IR_Analysis_Data		(uint32	nTimeL	);
void	__ATTR_SECTION_SRAM__  __attribute__((used))	LC_Key_Pin_IntHandler	(GPIO_Pin_e pin, IO_Wakeup_Pol_e type);
void	__ATTR_SECTION_SRAM__  __attribute__((used))	LC_Gpio_IR_IntHandler	(GPIO_Pin_e pin, IO_Wakeup_Pol_e type);
#ifdef	__cplusplus
	}
#endif

#endif	/**	LC_Event_Handler.h **/
/**	@}*/

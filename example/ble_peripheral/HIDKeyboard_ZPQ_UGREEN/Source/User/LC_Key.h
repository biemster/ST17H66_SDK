/**
*	@file	LC_Key.h
*	@date	09/17/2020
*	@version	1.0.0
*
*/

/*!
 * 	@defgroup	LC_Key
 *	@brief
 *	@{*/

#ifndef LC_KEY_H_
#define LC_KEY_H_

/*------------------------------------------------------------------*/
/*						C++ guard macro								*/
/*------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif
/*------------------------------------------------------------------*/
/*						head files include 							*/
/*------------------------------------------------------------------*/
#include "LC_Common.h"
#include "LC_UI_Led_Buzzer.h"
/*------------------------------------------------------------------*/
/*						Pins definitions							*/
/*------------------------------------------------------------------*/
#define MY_KEY_NO1_GPIO P14
// #define		MY_KEY_NO2_GPIO		P18
// #define		MY_KEY_NO3_GPIO		P15
// #define		MY_KEY_NO4_GPIO		P34
// #define		MY_KEY_NO5_GPIO		P7

/*------------------------------------------------------------------*/
/*						UI Task Events definitions					*/
/*------------------------------------------------------------------*/
#define		KEY_EVENT_LEVEL1	0x0010
#define		KEY_SYS_RESET		0x0020
#define		KEY_EVENT_SCANF		0x0040

#define		KEY_SCANF_EVT		0x0001
#define		KEY_STOPSCANF_EVT	0x0002

/*------------------------------------------------------------------*/
/*						Data structures								*/
/*------------------------------------------------------------------*/
typedef struct
{
	uint32 key_down_sys_tick; //	system time when key down
	uint8 key_down_flag;      //	1:key down	0:key release
	uint8 key_repeated_num;   //	times of key down
} lc_key_struct_data;

typedef enum
{
	KEY_NO_VALUE = 0,
	KEY_NO1_VALUE = 1,
	KEY_NO2_VALUE,
	KEY_NO3_VALUE,
	KEY_NO4_VALUE,
	KEY_NO5_VALUE,
} lc_key_press_value;
/*------------------------------------------------------------------*/
/*						external variables							*/
/*------------------------------------------------------------------*/
extern uint8 LC_Key_TaskID;
extern lc_key_struct_data LC_Key_Param;
/*------------------------------------------------------------------*/
/*						User function prototypes					*/
/*------------------------------------------------------------------*/
extern void Key_Pin_Config(void);
extern void LC_Key_Gpio_Init(void);
extern void LC_Key_Task_Init(uint8 task_id);
extern uint16 LC_Key_ProcessEvent(uint8 task_id, uint16 events);
extern void LC_Key_Pin_IntHandler(GPIO_Pin_e pin, IO_Wakeup_Pol_e type);

#ifdef __cplusplus
}
#endif

#endif /* LC_KEY_H_ */
/** @}*/

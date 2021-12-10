/**
*	@file	LC_UI_led_buzzer.h
*	@date	09/16/2020
*	@version	1.0.0
*
*/

/*!
 * 	@defgroup	LC_UI_led_buzzer
 *	@brief
 *	@{*/

#ifndef	LC_UI_LED_BUZZER_H_
#define	LC_UI_LED_BUZZER_H_
/*------------------------------------------------------------------*/
/*						C++ guard macro								*/
/*------------------------------------------------------------------*/
#ifdef	__cplusplus
extern	"C"	{
#endif
/*------------------------------------------------------------------*/
/*						head files include 							*/
/*------------------------------------------------------------------*/
#include "LC_Common.h"
#include "LC_Key.h"
#include "LC_ADC.h"
/*------------------------------------------------------------------*/
/*						Pins definitions							*/
/*------------------------------------------------------------------*/
#define		MY_GPIO_LED_NO1	P3		//	green LED
#define		MY_GPIO_LED_NO2	P7		//	red LED
#define		MY_GPIO_LED_NO3	GPIO_DUMMY
#define		MY_GPIO_PWM_NO1	GPIO_DUMMY
#define		MY_GPIO_PWM_NO2	GPIO_DUMMY
#define		MY_GPIO_PWM_NO3	GPIO_DUMMY

#define     MY_POWER_HOLD   P18

#define		BUZZER_FREQ		740
#define		BUZZER_DUTY		370
/*------------------------------------------------------------------*/
/*						UI Task Events definitions					*/
/*------------------------------------------------------------------*/
#define		UI_EVENT_LEVEL1	0x0001
#define		UI_EVENT_LEVEL2	0x0002
/*------------------------------------------------------------------*/
/*						Data structures								*/
/*------------------------------------------------------------------*/
typedef struct
{
	uint16			offOn_Ms[2];
	uint8			offOn_cnt;
	uint8			next_mode;
}lc_ui_mode_para;

typedef struct
{
	lc_ui_mode_para *ui_type;
	uint8			cur_mode;
	uint8			cur_cnt;
	uint8			cur_state;
	uint32			next_wakeup_tick;
}lc_ui_run_para;
/*------------------------------------------------------------------*/
/*						external variables							*/
/*------------------------------------------------------------------*/
extern uint8	LC_Ui_Led_Buzzer_TaskID;
/*------------------------------------------------------------------*/
/*						User function prototypes					*/
/*------------------------------------------------------------------*/
extern	void	LC_Led_No1_Onoff					(uint8 Onoff);
extern	void 	LC_Led_No1_Enter_Mode				(uint8 mode, uint8	time);
extern	void 	LC_Led_No2_Enter_Mode				(uint8 mode, uint8	time);
extern	void 	LC_Led_No3_Enter_Mode				(uint8 mode				);
extern	void 	LC_Buzzer_Enter_Mode				(uint8 mode				);
extern	void	LC_Switch_Poweron					(uint8 cur_state, uint8 power_start_tick);
extern	void	LC_Dev_Suspend						(void		);
extern	void 	LC_Dev_Poweroff						(uint8 poweroff_led_enable);
extern	void 	LC_UI_Led_Buzzer_Task_Init			(uint8 task_id);
extern	uint16	LC_UI_Led_Buzzer_ProcessEvent		(uint8 task_id, uint16 events);


#ifdef	__cplusplus
}
#endif

#endif	/*	LC_UI_LED_BUZZER_H_	*/
/**	@}*/

/**
 *	@file		LC_ADC.h
 *	@date		10/19/2020
 *	@version	1.0.0
 */

/*!
 *	@defgroup	LC_ADC
 *	@brief
 *	@{*/

#ifndef		LC_ADC_H_
#define		LC_ADC_H_
/*------------------------------------------------------------------*/
/*						C++ guard macro								*/
/*------------------------------------------------------------------*/
#ifdef	__cplusplus
	extern "C"	{
#endif
/*------------------------------------------------------------------*/
/*						head files include 							*/
/*------------------------------------------------------------------*/
#include "LC_Common.h"
/*------------------------------------------------------------------*/
/*						Pins definitions							*/
/*------------------------------------------------------------------*/
#define		MY_ADC_NO1_GPIO			P18
/*------------------------------------------------------------------*/
/*						MACROS										*/
/*------------------------------------------------------------------*/
//	battery pecent
#define		MY_BATT_PECENT_MAX		100
#define		MY_BATT_PECENT_75		75
#define		MY_BATT_PECENT_50		50
#define		MY_BATT_PECENT_25		25
#define		MY_BATT_PECENT_MIN		0
/*------------------------------------------------------------------*/
/*						UI Task Events definitions					*/
/*------------------------------------------------------------------*/
#define		ADC_EVENT_LEVEL1		0x1000
#define		ADC_EVENT_LEVEL2		0x2000
/*------------------------------------------------------------------*/
/*						Data structures								*/
/*------------------------------------------------------------------*/
typedef		struct{
	uint32	adc_simp_value;	//	adc value
}lc_adc_struct_data;
/*------------------------------------------------------------------*/
/*						external variables							*/
/*------------------------------------------------------------------*/
extern		uint8					LC_ADC_TaskID;
extern		lc_adc_struct_data		LC_ADC_Param;
extern		uint8					battLevel;

/*------------------------------------------------------------------*/
/*						User function prototypes					*/
/*------------------------------------------------------------------*/
extern		void 	LC_ADC_Gpio_Init			(void);
extern		int 	LC_ADC_Channel_Init		(void);
extern		void 	LC_ADC_Handler_Evt			(adc_Evt_t* pev					);
extern		void 	LC_ADC_Task_Init			(uint8 task_id					);
extern		uint16	LC_ADC_ProcessEvent		(uint8 task_id, uint16 events	);

#ifdef	__cplusplus
	}
#endif

#endif	/**	LC_ADC.h **/
/**	@}*/

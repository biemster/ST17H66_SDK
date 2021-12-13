/**
 *	@file		LC_ADC.c
 *	@date		10/19/2020
 *	@version	1.0.0
 */

/*!
 *  @defgroup	 LC_ADC
 *  @brief
 *  @{*/
 
#include "LC_ADC.h"
#include "LC_UI_led_buzzer.h"
uint8	LC_ADC_TaskID;
lc_adc_struct_data	LC_ADC_Param	=	{
	.adc_simp_value		=	0,
};

adc_Cfg_t	LC_ADC_CFG	=	{
	.channel	=	ADC_BIT(ADC_CH1P_P23),
	.is_continue_mode 	=	FALSE,
	.is_differential_mode	=	0,
	.is_high_resolution	=	0xff&(~ ADC_BIT(ADC_CH1P_P23)),//
};

/*!
 *	@fn			LC_ADC_Gpio_Init
 *	@brief		Initialize ADC pins.
 *	@param[in]	none.
 *	@return		none.
 */
void LC_ADC_Gpio_Init(void)
{
//	hal_gpio_cfg_analog_io(MY_ADC_NO1_GPIO, Bit_ENABLE);
}

uint8	LC_ADC_GP23_Measure(void)
{
	int ret;
	uint8_t	batt_ch	=	ADC_CH1P_P23;
	GPIO_Pin_e	pin;

	if((((1 << batt_ch) & LC_ADC_CFG.channel) == 0) || (LC_ADC_CFG.is_differential_mode != 0))
		return	PPlus_ERR_NOT_SUPPORTED;

	pin	=	s_pinmap[batt_ch];
	hal_gpio_cfg_analog_io(pin, Bit_DISABLE);
	hal_gpio_write(pin, 1);
	ret	=	hal_adc_config_channel(LC_ADC_CFG, LC_ADC_Handler_Evt);
	hal_gpio_cfg_analog_io(pin, Bit_DISABLE);

	if(ret){
		LOG("RET = %d\n",ret);
		return ret;
	}
	hal_adc_start();
	return PPlus_SUCCESS;
}
/*!
 *	@fn			LC_ADC_Channel_Init
 *	@brief		Initialize
 *	@param[in]	ADC data struct pointer.
 *	@return		none.
 */
int LC_ADC_Channel_Init(void)
{
	int ret;
	ret	=	LC_ADC_GP23_Measure();
//	ret = hal_adc_config_channel(LC_ADC_CFG, LC_ADC_Handler_Evt);
	if(ret)
		return ret;
	return PPlus_SUCCESS;
}
/*!
 *	@fn			LC_ADC_Handler_Evt
 *	@brief		deal with ADC simple datas.
 *	@param[in]	ADC data struct pointer.
 *	@return		none.
 */
void LC_ADC_Handler_Evt(adc_Evt_t* pev)
{
	bool	is_high_resolution		=	FALSE;
	bool	is_differential_mode	=	FALSE;
	float	adc_result	=	0;
	static	uint8	check_flag		=	0;
	if(pev->type == HAL_ADC_EVT_DATA){
		if(pev->ch == ADC_CH1P_P23){
			is_high_resolution		=	(LC_ADC_CFG.is_high_resolution & ADC_BIT(ADC_CH1P_P23))?TRUE:FALSE;
			is_differential_mode	=	(LC_ADC_CFG.is_differential_mode & ADC_BIT(ADC_CH1P_P23))?TRUE:FALSE;
			adc_result	=	hal_adc_value_cal((adc_CH_t)(ADC_CH1P_P23),pev->data,pev->size, is_high_resolution,is_differential_mode);
			LC_ADC_Param.adc_simp_value	=	(int)(adc_result*1000);
//			LOG("ADC simple data:%d\n",LC_ADC_Param.adc_simp_value);
			LC_ADC_Param.adc_simp_value	=	LC_ADC_Param.adc_simp_value + 100;
			LOG("ADC simple data:%d\n",LC_ADC_Param.adc_simp_value);


//			battLevel	=	LC_Dev_System_Param.dev_batt_value;
			if((LC_ADC_Param.adc_simp_value < 2450) && (LC_Dev_System_Param.dev_ble_con_state == LC_DEV_BLE_CONNECTION)){//
				LC_Led_No2_Enter_Mode(1,1);
			}
			check_flag	=	0x02;
		}
		if(check_flag == 0x02){
			check_flag	=	0;
			osal_start_timerEx(LC_ADC_TaskID, ADC_EVENT_LEVEL2, 20);
		}
	}
}
/*!
 *	@fn			LC_ADC_Task_Init
 *	@brief		Initialize function for the ADC task.
 *	@param[in]	task_id:	the ID assigned by OSAL,
 *							used to send message and set timer.
 *	@return		none.
 */
void LC_ADC_Task_Init(uint8 task_id)
{
	LC_ADC_TaskID	=	task_id;
	if(LC_Dev_System_Param.dev_power_flag){
		osal_start_timerEx(LC_ADC_TaskID, ADC_EVENT_LEVEL1, 10*1000);
		LOG("ADC Init ~~\n");
	}
	
}

/*!
 *	@fn			LC_ADC_ProcessEvent
 *	@brief		ADC Task event processor.This function
 *				is called to processs all events for the task.Events
 *				include timers,messages and any other user defined events.
 *	@param[in]	task_id			:The OSAL assigned task ID.
 *	@param[in]	events			:events to process.This is a bit map and can
 *									contain more than one event.
 *	@return  	events not processed.
 */
uint16	LC_ADC_ProcessEvent(uint8 task_id, uint16 events)
{
	VOID task_id;	// OSAL required parameter that isn't used in this function
	if(events & SYS_EVENT_MSG){
		uint8	*pMsg;
		if((pMsg = osal_msg_receive(LC_ADC_TaskID)) != NULL){
			LC_Common_ProcessOSALMsg((osal_event_hdr_t *)pMsg);
            // Release the OSAL message
			VOID osal_msg_deallocate(pMsg);
		}
		return(events ^ SYS_EVENT_MSG);
	}
	if(events & ADC_EVENT_LEVEL1){
		hal_adc_stop();
		hal_adc_init();
		LC_ADC_Channel_Init();
		hal_adc_start();

		osal_start_timerEx(LC_ADC_TaskID, ADC_EVENT_LEVEL1, 15*1000);
		return(events ^ ADC_EVENT_LEVEL1);
	}
	if(events & ADC_EVENT_LEVEL2){
		hal_adc_stop();
		return(events ^ ADC_EVENT_LEVEL2);
	}

	return 0;
}
/** @}*/


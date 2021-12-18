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
 
#include "LC_UI_Led_Buzzer.h"

uint8	LC_Ui_Led_Buzzer_TaskID;
lc_ui_mode_para	Led_No1_Mode_Ms[]	=	{
	//off			on		cnt 	next mode
	{{0,			0}, 	0,		0},
	{{0, 			4500},	0x01,	2},
	{{1000,			1300},	0xff,	2}, 
	{{0,			400},	0xff,	3},
	{{0,			6000},	0x01,	0},
	{{1000,			60},	0x28,	0},
	{{180,			60},	0xff,	0},
};
lc_ui_mode_para	Led_No2_Mode_Ms[]	=	{
	//off			on		cnt 	next mode
	{{0,			0}, 	0,		0},
	{{900, 			100},	0xff,	0},
	{{0,			200},	0x19,	0}, 
	{{0,			100},	0x01,	0},
};
lc_ui_mode_para	Led_No3_Mode_Ms[]	=	{
	//off			on		cnt 	next mode
	{{0,			0}, 	0,		0},
	{{1900, 		100},	0xff,	1},
	{{0,			200},	0x19,	0}, 
	{{0,			100},	0x01,	0},
};
lc_ui_mode_para	Buzzer_Mode_Ms[]	=	{
	//off			on		cnt 	next mode
	{{0,			0}, 	0,		0},    
	{{400,			100},	0x02,	0}, 
	{{0,			50},	0x01,	0}, 	
	{{300,			100},	0xff,	3}, 
};
lc_ui_run_para	Led_No1_Param	=	{Led_No1_Mode_Ms};
lc_ui_run_para	Led_No2_Param	=	{Led_No2_Mode_Ms};
lc_ui_run_para	Led_No3_Param	=	{Led_No3_Mode_Ms};
lc_ui_run_para	Buzzer_Param	=	{Buzzer_Mode_Ms};

/*!
 *	@fn			LC_UI_Led_Buzzer_Gpio_Init
 *	@brief		Initialize the LED and Buzzer pins. 
 *	@param[in]	none.
 *	@return		none.
 */
void LC_UI_Led_Buzzer_Gpio_Init(void)
{


	hal_gpio_pin_init(MY_GPIO_LED_NO1, OEN) ;
	hal_gpioretention_register(MY_GPIO_LED_NO1);
	hal_gpio_write(MY_GPIO_LED_NO1, 0) ;


	hal_gpio_pin_init(MY_GPIO_LED_NO2, OEN) ;
	hal_gpioretention_register(MY_GPIO_LED_NO2);
	hal_gpio_write(MY_GPIO_LED_NO2, 0) ;
}
/*!
 *	@fn			LC_Pwm_Contorl
 *	@brief		Control the duty and frequence of PWM
 *	@param[in]	pwm_ch		:channel of PWM
 *	@param[in]	duty_value	:frequence of pwm
 *	@return		success or err.
 */
uint8	LC_Pwm_Contorl(uint8 pwm_ch, uint16 duty_value)
{

	if( (pwm_ch > 3) || (duty_value > BUZZER_FREQ)){
		return PPlus_ERR_INVALID_PARAM;
	}
	switch(pwm_ch){
		case	0:
			if(duty_value == 0){
				hal_gpio_write(MY_GPIO_PWM_NO1, 0);
				
//				hal_gpio_fmux(MY_GPIO_PWM_NO1, Bit_DISABLE);
//				hal_gpio_pin_init(MY_GPIO_PWM_NO1, IE);
//				hal_gpio_pull_set(MY_GPIO_PWM_NO1, PULL_DOWN);
			}else{
				hal_pwm_init(PWM_CH0, PWM_CLK_DIV_8, PWM_CNT_UP, PWM_POLARITY_FALLING);
				hal_pwm_open_channel(PWM_CH0, MY_GPIO_PWM_NO1);
				hal_pwm_start();

				hal_pwm_set_count_val(PWM_CH0, BUZZER_DUTY, BUZZER_FREQ);
			}
		break;

		default:
		break;
	}
	return	PPlus_SUCCESS;
}

uint8	LC_Pwm_On(uint8 pwm_ch)
{
	switch(pwm_ch){
		case	0:
			hal_pwm_init(PWM_CH0, PWM_CLK_DIV_8, PWM_CNT_UP, PWM_POLARITY_FALLING);
			hal_pwm_set_count_val(PWM_CH0, BUZZER_DUTY, BUZZER_FREQ);
			hal_pwm_open_channel(PWM_CH0, MY_GPIO_PWM_NO1);
		break;
		default:
		break;
	}
	hal_pwm_start();
	return PPlus_SUCCESS;
}
uint8	LC_Pwm_Off(uint8 pwm_ch)
{
	switch(pwm_ch){
		case 0:
			hal_pwm_close_channel(PWM_CH0);
			hal_pwm_destroy(PWM_CH0);
		break;

		default:
		break;
	}
	hal_pwm_stop();
	return PPlus_SUCCESS;
}
/*!
 *	@fn			LC_Led_No1_Onoff
 *	@brief		led and buzzer on-off state control.
 *	@param[in]	Onoff		:the state of led or buzzer
 *	@return		none.
 */
void LC_Led_No1_Onoff(uint8 Onoff)
{
	if(Onoff){
		hal_gpio_write(MY_GPIO_LED_NO1, 1);
	}else{
		hal_gpio_write(MY_GPIO_LED_NO1, 0);
	}
}
void LC_Led_No2_Onoff(uint8 Onoff)
{
	if(Onoff){
		hal_gpio_write(MY_GPIO_LED_NO2, 1);
	}else{
		hal_gpio_write(MY_GPIO_LED_NO2, 0);
	}
}
void LC_Led_No3_Onoff(uint8 Onoff)
{
	if(Onoff){
		hal_gpio_write(MY_GPIO_LED_NO3, 1);
	}else{
		hal_gpio_write(MY_GPIO_LED_NO3, 0);
	}
}
void LC_Buzzer_Onoff(uint8 Onoff)
{
	if(Onoff){
		LC_Pwm_On(0);
		LC_Pwm_Contorl(0, BUZZER_DUTY);
	}else{
		LC_Pwm_Off(0);
		hal_gpio_fmux(MY_GPIO_PWM_NO1, Bit_DISABLE);
		hal_gpio_pin_init(MY_GPIO_PWM_NO1, IE);
		hal_gpio_pull_set(MY_GPIO_PWM_NO1, PULL_DOWN);
	}
}
/*!
 *	@fn			LC_UI_Cacl
 *	@brief		Caculate the ui wakeup time.
 *	@param[in]	ui_bl		:current running parameter of led or buzzer.
 *	@return		running time of led.
 */
uint32 LC_UI_Cacl(lc_ui_run_para *ui_bl)
{
	if(ui_bl->cur_mode == 0) return 0;

	if(ui_bl->next_wakeup_tick - ((hal_systick()|1) + 2) < BIT(30)){
		return ui_bl->next_wakeup_tick;
	}
	if(ui_bl->cur_state && ui_bl->cur_cnt && ui_bl->cur_cnt != 0xff){//!=0 !=0xff ==on
		ui_bl->cur_cnt --;
	}
	if(ui_bl->cur_cnt == 0 ){
		ui_bl->cur_mode = ui_bl->ui_type[ui_bl->cur_mode].next_mode;
		ui_bl->cur_cnt = ui_bl->ui_type[ui_bl->cur_mode].offOn_cnt;
	}
	if(ui_bl->cur_cnt && ui_bl->ui_type[ui_bl->cur_mode].offOn_Ms[0] == 0){
		ui_bl->cur_state = 1;
	}else {
		ui_bl->cur_state = ui_bl->cur_state ? 0: 1;
	}
	//ui_bl->cur_state = ui_bl->cur_state ? 0: 1;
	ui_bl->next_wakeup_tick = hal_systick() + ui_bl->ui_type[ui_bl->cur_mode].offOn_Ms[ui_bl->cur_state] ;
	return ui_bl->next_wakeup_tick;
}
/*!
 *	@fn				LC_UI_Tick_Process
 *	@brief			deal the mode of led or buzzer,and manage power.
 *	@param[in]		none.
 *	@retrurn		none.
 */
uint32 LC_UI_Tick_Process(void)
{
	static	uint32	next_led_wakeup_timerout	=	0;
	uint32	next_led_wakeup_tick_1	=	LC_UI_Cacl(&Led_No1_Param);
	uint32	next_led_wakeup_tick_2	=	LC_UI_Cacl(&Led_No2_Param);
//	uint32	next_led_wakeup_tick_3	=	LC_UI_Cacl(&Led_No3_Param);
//	uint32	next_buzzer_wakeup_tick	=	LC_UI_Cacl(&Buzzer_Param);

	if(Led_No1_Param.cur_mode || Led_No2_Param.cur_mode)
	{
		if(Led_No1_Param.cur_state || Led_No2_Param.cur_state){
			LC_Dev_System_Param.dev_lowpower_flag	=	1;
			next_led_wakeup_timerout	=	hal_systick()|1;
		}else{
			LC_Dev_System_Param.dev_lowpower_flag	=	0;
		}
	}else{
		if(next_led_wakeup_timerout && clock_time_exceed_func(next_led_wakeup_timerout, 100)){
			LC_Dev_System_Param.dev_lowpower_flag	=	0;
			next_led_wakeup_timerout	=	0;
		}
	}


	if(LC_Dev_System_Param.dev_lowpower_flag	!=	2){
		hal_pwrmgr_unlock(MOD_USR8);	//	low power mode
	}else{
		hal_pwrmgr_lock(MOD_USR8);
	}

	LC_Led_No1_Onoff(Led_No1_Param.cur_state);
	LC_Led_No2_Onoff(Led_No2_Param.cur_state);
//	LC_Led_No3_Onoff(Led_No3_Param.cur_state);
//	LC_Buzzer_Onoff(Buzzer_Param.cur_state);

	return	next_led_wakeup_tick_1;
}
/*!
 *	@fn			LC_UI_Enter_Mode
 *	@brief		change led or buzzer mode.
 *	@param[in]	ui_param	:all mode parameters of led or buzzer.
 *	@param[in]	mode		:wanted mode.
 *	@return		none.
 */
void LC_UI_Enter_Mode(lc_ui_run_para *ui_param, uint8 mode)
{
	ui_param->cur_cnt = ui_param->ui_type[mode].offOn_cnt;
	ui_param->cur_mode = mode;
	ui_param->cur_state = 0;
	ui_param->next_wakeup_tick = hal_systick()|1;
}
void LC_Led_No1_Enter_Mode(uint8 mode, uint8	time)
{
	LC_UI_Enter_Mode(&Led_No1_Param, mode);
	if(LC_Dev_System_Param.dev_power_flag&&time){
		// LC_Dev_System_Param.dev_lowpower_flag	=	1;
		// osal_start_timerEx(LC_Ui_Led_Buzzer_TaskID, UI_EVENT_LEVEL1, 5);
		osal_set_event(LC_Ui_Led_Buzzer_TaskID, UI_EVENT_LEVEL1);
	}
}
void LC_Led_No2_Enter_Mode(uint8 mode, uint8	time)
{
	LC_UI_Enter_Mode(&Led_No2_Param, mode);
	if(LC_Dev_System_Param.dev_power_flag && time){
		// LC_Dev_System_Param.dev_lowpower_flag	=	1;
		// osal_start_timerEx(LC_Ui_Led_Buzzer_TaskID, UI_EVENT_LEVEL1, 5);
		osal_set_event(LC_Ui_Led_Buzzer_TaskID, UI_EVENT_LEVEL1);
	}
}
void LC_Led_No3_Enter_Mode(uint8 mode)
{
	LC_UI_Enter_Mode(&Led_No3_Param, mode);
}
void LC_Buzzer_Enter_Mode(uint8 mode)
{
	LC_UI_Enter_Mode(&Buzzer_Param, mode);
}
/*!
 *	@fn			LC_Switch_Poweron
 *	@brief		press switch to power on.
 *	@param[in]	cur_state	:
 *	@param[in]	power_start_tick	:set time for long press to poweron,
 *									power_start_tick*25ms
 *	@return		none.
 */
void LC_Switch_Poweron(uint8 cur_state, uint8 power_start_tick)
{
	if(LC_Dev_System_Param.dev_poweron_switch_flag)
	{
		LC_Dev_System_Param.dev_power_flag		=	SYSTEM_WORKING;
		return;
	}
	uint8	poweron_start_num	=	power_start_tick;
	static	uint32	poweron_start_time_100ms;
	if(!cur_state){
		while(poweron_start_num){
			WaitUs(1000);
			if(clock_time_exceed_func(poweron_start_time_100ms, 25)){
				poweron_start_time_100ms	=	hal_systick() | 1;
				if(!hal_gpio_read(MY_KEY_NO1_GPIO)){
					poweron_start_num--;
				}else{
					poweron_start_num	=	power_start_tick;
					LC_Dev_System_Param.dev_power_flag		=	SYSTEM_STANDBY;
					LC_Dev_Poweroff(0);
					return ;
				}
			}
		}
		poweron_start_time_100ms	=	hal_systick() | 1;
		while(!hal_gpio_read(MY_KEY_NO1_GPIO)){		//	release key after power on if key didn't release
			if(clock_time_exceed_func(poweron_start_time_100ms, 500)){
				poweron_start_time_100ms	=	hal_systick() | 1;
				LC_Dev_System_Param.dev_power_flag		=	SYSTEM_WORKING;
				return;
			}
		}
		LC_Dev_System_Param.dev_power_flag		=	SYSTEM_WORKING;
	}
}
/*!
 *	@fn			LC_Dev_Suspend
 *	@brief		the process of suspend,disable adv.
 *	@param[in]	none.
 *	@return		none.
 */
void	LC_Dev_Suspend(void)
{
	LOG("system enter suspend\n");
	LC_Led_No1_Onoff(State_Off);
	LC_Led_No2_Onoff(State_Off);
	hal_pwrmgr_unlock(MOD_USR8);
    LC_Dev_System_Param.dev_power_flag	=	SYSTEM_SUSPEND;
    LC_Dev_System_Param.dev_timeout_suspend_cnt	=	LC_DEV_TIMER_SUSPEND;
	uint8 initial_advertising_enable    =   FALSE;
	GAPRole_SetParameter( GAPROLE_ADVERT_ENABLED, sizeof( uint8 ), &initial_advertising_enable );
}
/*!
 *	@fn			LC_Dev_Poweroff
 *	@brief		the process of power off,need to disable adv and all events.
 *	@param[in]	none.
 *	@return		none.
 */
void LC_Dev_Poweroff(uint8 poweroff_led_enable)
{
	if(poweroff_led_enable){
		for(uint8 i	= 0;i<6;i++){
			LC_Led_No1_Onoff(i&0x01);
			WaitUs(100*1000);
		}
		LC_Led_No1_Onoff(0);
		WaitUs(10*1000);
	}
	LOG("Power off led [%d],,system flag[%d]\n",poweroff_led_enable, LC_Dev_System_Param.dev_power_flag);
	GAPRole_TerminateConnection();
    hal_gpio_fmux(MY_POWER_HOLD, Bit_DISABLE);
    hal_gpio_pin_init(MY_POWER_HOLD, IE);
    hal_gpio_pull_set(MY_POWER_HOLD, PULL_DOWN);

	pwroff_cfg_t	User_Set_Wakeup;
	User_Set_Wakeup.pin	=	MY_KEY_NO1_GPIO;
	User_Set_Wakeup.type	=	NEGEDGE;
	User_Set_Wakeup.on_time	=	1;

	hal_pwrmgr_unlock(MOD_USR8);
	if(poweroff_led_enable){
		AP_WDT->CRR	=	0x76;	//	feed watch dog
		while(!hal_gpio_read(MY_KEY_NO1_GPIO)){
			WaitUs(10*1000);
			AP_WDT->CRR	=	0x76;	//	feed watch dog
		}
	}

	hal_pwrmgr_poweroff(&User_Set_Wakeup, 1);

}

void	LC_Working_Timer(void){
	LC_Dev_System_Param.dev_timeout_poweroff_cnt--;
	LOG("system tiemr WORKING = [%d]*6s\n",LC_Dev_System_Param.dev_timeout_poweroff_cnt);
	if(LC_Dev_System_Param.dev_timeout_poweroff_cnt == 0){
		osal_stop_timerEx(LC_Ui_Led_Buzzer_TaskID, UI_EVENT_LEVEL2);
	#if(LC_ZPQ_SUSPEND_ENABLE == 1)
		if(LC_Dev_System_Param.dev_ble_con_state	==	LC_DEV_BLE_CONNECTION){
			GAPRole_TerminateConnection();
		}else{
			LC_Dev_Suspend();
		}
	#else
		LC_Dev_System_Param.dev_power_flag	=	SYSTEM_STANDBY;
	#endif
	}
}

void	LC_Suspend_Timer(void)
{
	LC_Dev_System_Param.dev_timeout_suspend_cnt--;
	LOG("system tiemr SUSPEND = [%d]*6s\n",LC_Dev_System_Param.dev_timeout_suspend_cnt);
	if(LC_Dev_System_Param.dev_timeout_suspend_cnt == 0){
		LC_Dev_System_Param.dev_power_flag	=	SYSTEM_STANDBY;
	}
}

/*!
 *	@fn			LC_UI_Led_Buzzer_Task_Init 
 *	@brief		Initialize function for the UI_LED_BUZZER Task. 
 *	@param[in]	task_id			:the ID assigned by OSAL,
 *								used to send message and set timer.
 *	@retrurn	none.
 */
void LC_UI_Led_Buzzer_Task_Init(uint8 task_id)
{
	LC_Ui_Led_Buzzer_TaskID	=	task_id;
	LOG("LC_UI_Led_Buzzer_Gpio_Init:\n");
	LC_UI_Led_Buzzer_Gpio_Init();
	LC_Key_Gpio_Init();
	LC_Timer_Start();

	if(LC_Dev_System_Param.dev_power_flag){	
		osal_start_timerEx(LC_Ui_Led_Buzzer_TaskID, UI_EVENT_LEVEL1, 20);
		osal_start_timerEx(LC_Ui_Led_Buzzer_TaskID, UI_EVENT_LEVEL2, 100);
	}
}
/*!
 *	@fn			LC_UI_Led_Buzzer_ProcessEvent
 *	@brief		UI_LED_BUZZER Task event processor.This function
 *				is called to processs all events for the task.Events
 *				include timers,messages and any other user defined events.
 *	@param[in]	task_id			:The OSAL assigned task ID.
 *	@param[in]	events			:events to process.This is a bit map and can
 *									contain more than one event.
 */
uint16	LC_UI_Led_Buzzer_ProcessEvent(uint8 task_id, uint16 events)
{
	VOID task_id;	// OSAL required parameter that isn't used in this function
	if(events & SYS_EVENT_MSG){
		uint8	*pMsg;
		if((pMsg = osal_msg_receive(LC_Ui_Led_Buzzer_TaskID)) != NULL){
			LC_Common_ProcessOSALMsg((osal_event_hdr_t *)pMsg);
            // Release the OSAL message
			VOID osal_msg_deallocate(pMsg);
		}
		return(events ^ SYS_EVENT_MSG);
	}
	if(events & UI_EVENT_LEVEL1){
		if(LC_Dev_System_Param.dev_power_flag == SYSTEM_WORKING){
			LC_UI_Tick_Process();
			if(LC_Dev_System_Param.dev_lowpower_flag	==	2){
				osal_start_timerEx(LC_Ui_Led_Buzzer_TaskID, UI_EVENT_LEVEL1, 50);
			}else if(LC_Dev_System_Param.dev_lowpower_flag	==	1){
				osal_start_timerEx(LC_Ui_Led_Buzzer_TaskID, UI_EVENT_LEVEL1, 100);
			}else{
				osal_start_timerEx(LC_Ui_Led_Buzzer_TaskID, UI_EVENT_LEVEL1, 500);
			}
		}else if(LC_Dev_System_Param.dev_power_flag	== SYSTEM_SUSPEND){
			LC_Suspend_Timer();
			osal_start_timerEx(LC_Ui_Led_Buzzer_TaskID, UI_EVENT_LEVEL1, 6000);
		}else if(LC_Dev_System_Param.dev_power_flag == SYSTEM_STANDBY){
			LC_Dev_Poweroff(1);
		}
		return(events ^ UI_EVENT_LEVEL1);
	}

	if(events & UI_EVENT_LEVEL2){
		if(LC_Dev_System_Param.dev_power_flag == SYSTEM_WORKING){
			osal_start_timerEx(LC_Ui_Led_Buzzer_TaskID, UI_EVENT_LEVEL2, 6*1000);
			LC_Working_Timer();
		}
		return(events ^ UI_EVENT_LEVEL2);
	}
    // Discard unknown events
//	osal_start_timerEx(LC_Ui_Led_Buzzer_TaskID, UI_EVENT_LEVEL1, 1000);
    return 0;
}
/** @}*/


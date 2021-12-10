/**
*	@file	LC_Common.h
*	@date	09/17/2020
*	@version	1.0.0
*
*/

/*!
 * 	@defgroup	LC_Common
 *	@brief
 *	@{*/
 
#include "LC_Common.h"

lc_dev_sys_param	LC_Dev_System_Param	=	
{
	.dev_timeout_poweroff_cnt	=	0xffffffff,
	.dev_timeout_suspend_cnt	=	LC_DEV_TIMER_SUSPEND,
	.dev_adv_change_tick		=	0,
	.dev_poweron_switch_flag	=	0,
	.dev_power_flag				=	0,
	.dev_lowpower_flag			=	0,
	.dev_ble_con_state			=	0,
	.dev_batt_value				=	0,
	.dev_adv_ctrl_num			=	0,
	.dev_adv_change_flag		=	0,
	.dev_keyconn_enable			=	0,
};
/*!
 *	@fn			clock_time_exceed_func
 *	@brief		
 */
uint32 clock_time_exceed_func(uint32 ref, uint32 span_ms)
{
#if 0
	u32 deltTick ,T0 ;
	T0 = hal_read_current_time();
	deltTick =TIME_DELTA(T0,ref);
	if(deltTick>span_ms){
		return 1 ;
	}else {
		return 0 ;
	}
#else 
	uint32 deltTick  = 0 ;
	deltTick = hal_ms_intv(ref) ;
	if(deltTick>span_ms){
		return 1 ;
	}else {
		return 0 ;
	}	
#endif
}
/*!
 *	@fn			LC_Common_ProcessOSALMsg
 *	@brief		Process an incoming task message,nothing.
 *	@param[in]	pMsg	:message to process
 *	@return		none.
 */
void LC_Common_ProcessOSALMsg(osal_event_hdr_t *pMsg)
{
	switch(pMsg->event)
	{
		default:
			// do nothing
		break;
	}
}
/*!
 *	@fn			Printf_Hex
 *	@brief		printf data.
 *	@param[in]	data	:pointer of datas,
 *	@param[in]	len		:length of datas,
 *	@return		none.
 */
void Printf_Hex (const uint8 *data, uint16 len)
{
    uint16 i;

    for (i = 0; i < len - 1; i++)
    {
        LOG("%x,",data[i]);
        LOG(" ");
    }
    LOG("%x\n",data[i]);
}

void LC_Timer_Start(void)
{
	// hal_timer_init(LC_Dev_TimerTOSuspend);
	// hal_timer_set(AP_TIMER_ID_5, 100);
	// hal_timer_set(AP_TIMER_ID_6, 5*1000);
//	LOG("Start timer:\n");
}
void LC_Timer_Stop(void)
{
	// hal_timer_stop(AP_TIMER_ID_5);
	// hal_timer_stop(AP_TIMER_ID_6);
//	LOG("Stop timer\n");
}
void	LC_Data_Push(uint8 cmd)
{
	if(cmd){
		hidCCSendReport(0,1,0);
	}else{
		hidCCSendReport(0,0,0);
	}
}
/** @}*/


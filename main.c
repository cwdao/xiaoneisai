/**********************************************************************
**  Copyright (c)  Smartcar Lab of USTB
**----------------------------------------------------------------------
**	Module Name: main.c
**	Module Date: 9/2018
**	Module Auth: Download By DAP
**  Description: School Match
**---------------------------------------------------

**********************************************************************/
#include "common.h"
int main(void)
{
  DisableInterrupts;           //关闭中断
  
  sysinit();                   //系统初始化，不要随意修改该函数
  
  system_init();               //系统初始化，不要随意修改该函数
  
  JM_STATUS_init();            //拨码开关初始化，调整策略
  
  PIDInit();                   //如果闭环的话速控参数初始化
    
  Delay_T1_mS(1000);           //延时1s
  
  EnableInterrupts;            //打开中断
  
  while(1)                     //空循环，因为定时中断已经打开，所以每隔5ms会执行一次schedule.c中的pit0_isr();
  {
//         SET_PWM_MOT(200);
//         SET_PWM_SVO(3500);
  }
}


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
  DisableInterrupts;           //�ر��ж�
  
  sysinit();                   //ϵͳ��ʼ������Ҫ�����޸ĸú���
  
  system_init();               //ϵͳ��ʼ������Ҫ�����޸ĸú���
  
  JM_STATUS_init();            //���뿪�س�ʼ������������
  
  PIDInit();                   //����ջ��Ļ��ٿز�����ʼ��
    
  Delay_T1_mS(1000);           //��ʱ1s
  
  EnableInterrupts;            //���ж�
  
  while(1)                     //��ѭ������Ϊ��ʱ�ж��Ѿ��򿪣�����ÿ��5ms��ִ��һ��schedule.c�е�pit0_isr();
  {
//         SET_PWM_MOT(200);
//         SET_PWM_SVO(3500);
  }
}


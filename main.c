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
int servo_testtest = 2340;
int motor_testtest = 180;
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
         //SET_PWM_MOT(motor_testtest);
         //SET_PWM_SVO(servo_testtest);
  }
}


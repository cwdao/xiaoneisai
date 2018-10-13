/*
* File:	schedule.c
* Purpose:
*
* Notes:
*/
#include "common.h"
#include "schedule.h"

/******************************************************************************/
/******************************D E F I N I T I O N ****************************/

//Magnet_Reed
uint8 Stop_Flag = 0;       //ͣ����־λ
uint16 servotest;          //���������
uint16 Motor_Test=30;      //���������
uint16 stopCnt;

//��ʱʱ��
uint16 g_time = 0;


//���PD���Ʋ���
float turn_p=16;
float turn_d=80;//80
float Kp,Kd;
uint8 lose_flag=0;

//���PID���Ʋ���
float g_speed_p;
float g_speed_i;
float g_speed_d;
int16 g_countervalue=0;

//���������
int16 servo;             //ƫת��

//�ٶȸ���
int16  g_speed_final;

/*---------------------------- F U N C T I O N S --------------------------------*/
//�жϺ������жϴ򿪺�5����ִ��һ��
void pit0_isr(void)
{
  PIT_ChannelClrFlags(0);

  //��ʱ����
  TIME0_RESET();

  //���AD�ɼ�
  adcollect();

  //ƫ��������
  adidentify();
  //Caculation();
  
  //���ɻɹܣ�ͣ����⺯��
  Magnet_detect();

  //JM_STATUS_init();
  //����������  ��һ��Ϊ����   ע����Ϊ�ջ����ƣ�ǰ�ڿɲ��ã�������ֻ����һ������
 //Car_Run_openloop();
  Car_Run_closedloop();

  //������ƺ���
  Car_Turn();

  g_time++;      //�жϼ���

} // �����ж�


/*===============================Car_Run=============================*/

void Car_Run_openloop(void)
{
  if(g_time<300 || Stop_Flag)     //g_time ��ʱʱ��  Stop_Flag ͣ����־λ
  {
    SET_PWM_MOT(0);
  }
  else
  {
    SET_PWM_MOT(250);
  }

}

void Car_Run_closedloop(void)
{
  
  //�ٶȷ����ɼ�
  g_countervalue = -Get_Counter_Value();
  sPID.vi_FeedBack = g_countervalue;
  
  if(g_time>500)          //2.5s�󷢳�
  {
    if(Stop_Flag || g_time>10000)
    {
      sPID.vi_Ref = 0;
    }
    else
    {
      sPID.vi_Ref = 30;
      if(AD[Left]+AD[Right]<200)
        sPID.vi_Ref = 20;
    }
  }
//   sPID.vi_Ref  = Motor_Test;
  SET_PWM_MOT(-V_PIDCalc(&sPID));
//  SET_PWM_MOT(Motor_Test);
 
}

/*===============================Car_Turn=============================*/
//
// Date��
// Notes:�������
/*====================================================================*/
void Car_Turn(void)
{
  
  
    if(AD[Left]+AD[Right]<100)
  {
    Kp=turn_p*3;
    Kd=turn_d*3;
  }
  else if(AD[Left]+AD[Right]<200)
  {
    Kp=turn_p*2;
    Kd=turn_d*2;
  }
  else
  {
    Kp=turn_p;
    Kd=turn_d;
  }
  
  servo=RUDDER_MIDDLE_TURN+(int)(Deviation*Kp/100)+(int)((Deviation-Pre_Deviation)*Kd/100);

  //��һ�β���ȥ�����������   ��ֹ�򵽼���λ�ã��𻵶��
  if(servo>SVO_MAX)
  {
    servo = SVO_MAX;
  }
  if(servo<SVO_MIN)
  {
    servo = SVO_MIN;
  }

  //���P��
    SET_PWM_SVO(servo);
//  SET_PWM_SVO(servotest);
}


/*=============================Magnet_detect===========================*/
void Magnet_detect(void)
{
  
  if(g_time>10000)              //������7.5s�ڲ����ͣ��
  {
    if(REED_1_Status==0||REED_2_Status==0)     //�ɻɹܼ��ͣ��
    {
      Stop_Flag=1;
    }
  }
  if(AD[Left]+AD[2]+AD[4]+AD[Right] <10 && g_time>1000)     // if(AD[Left]+AD[Middle]+AD[Right] <10 && g_time>1000)
  {

      stopCnt++;
  }
  else
  {
    stopCnt=0;
  }
  if(stopCnt>100)
  {
  Stop_Flag = 1;
  }
}


/**********************************************************
Function Name:JM_STATUS_init
Description:�������س�ʼ��,��������
Inputs:  None
Outputs: None
Notes:
***********************************************************/
void JM_STATUS_init(void)
{
  if(JM_2_STATUS==0&&JM_3_STATUS==0)
  {
    LED_0_OFF();                     //�õ��������жϲ���ѡ��
//    LED_2_OFF();
  }
  else if(JM_2_STATUS==1&&JM_3_STATUS==1)
  {
    LED_0_ON();
//    LED_2_OFF();
  }
  else if(JM_2_STATUS==1&&JM_3_STATUS==0)
  {
    LED_0_OFF();
    LED_2_ON();
  }
  else
  {
    LED_0_ON();
    LED_2_ON();
  }
}


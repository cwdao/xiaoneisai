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
uint8 Stop_Flag = 0;       //停车标志位
uint16 servotest;          //舵机测试量
uint16 Motor_Test=30;      //电机测试量
uint16 stopCnt;

//计时时间
uint16 g_time = 0;


//舵机PD控制参数
float turn_p=16;
float turn_d=80;//80
float Kp,Kd;
uint8 lose_flag=0;

//电机PID控制参数
float g_speed_p;
float g_speed_i;
float g_speed_d;
int16 g_countervalue=0;

//舵机控制量
int16 servo;             //偏转量

//速度给定
int16  g_speed_final;

/*---------------------------- F U N C T I O N S --------------------------------*/
//中断函数，中断打开后，5毫秒执行一次
void pit0_isr(void)
{
  PIT_ChannelClrFlags(0);

  //计时重置
  TIME0_RESET();

  //电感AD采集
  adcollect();

  //偏差量计算
  adidentify();
  //Caculation();
  
  //（干簧管）停车检测函数
  Magnet_detect();

  //JM_STATUS_init();
  //控制量计算  第一行为开环   注释行为闭环控制（前期可不用），两者只需用一个即可
 //Car_Run_openloop();
  Car_Run_closedloop();

  //舵机控制函数
  Car_Turn();

  g_time++;      //中断计数

} // 控制中断


/*===============================Car_Run=============================*/

void Car_Run_openloop(void)
{
  if(g_time<300 || Stop_Flag)     //g_time 计时时间  Stop_Flag 停车标志位
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
  
  //速度反馈采集
  g_countervalue = -Get_Counter_Value();
  sPID.vi_FeedBack = g_countervalue;
  
  if(g_time>500)          //2.5s后发车
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
// Date：
// Notes:舵机控制
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

  //这一段不能去掉，保护舵机   防止打到极限位置，损坏舵机
  if(servo>SVO_MAX)
  {
    servo = SVO_MAX;
  }
  if(servo<SVO_MIN)
  {
    servo = SVO_MIN;
  }

  //输出P波
    SET_PWM_SVO(servo);
//  SET_PWM_SVO(servotest);
}


/*=============================Magnet_detect===========================*/
void Magnet_detect(void)
{
  
  if(g_time>10000)              //发车后7.5s内不检测停车
  {
    if(REED_1_Status==0||REED_2_Status==0)     //干簧管检测停车
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
Description:拨档开关初始化,调整策略
Inputs:  None
Outputs: None
Notes:
***********************************************************/
void JM_STATUS_init(void)
{
  if(JM_2_STATUS==0&&JM_3_STATUS==0)
  {
    LED_0_OFF();                     //用灯亮灭辅助判断策略选择
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


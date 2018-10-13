/*
* File:	adidentify.c
* Purpose:
*
* Notes:
*/
#include "common.h"
#include "adidentify.h"
/******************************************************************************/
/******************************D E F I N I T I O N ****************************/
//定义偏差量
float Deviation = 0;
float Pre_Deviation = 0;
float middle_final = 0;
float pre_middle_final = 0;

float Linear_fit;
uint16 AD_left;
uint16 AD_right;
uint8 Curve_Flag=0;        //弯道标志

/**********************************************************
Function Name:sqrt
Description:  
Inputs:  None
Outputs: None
Notes:     求平方根
***********************************************************/
float sqrt(float a)
{
  
  float x, y;
  x = 0.0;
  y = a / 2;
  while (x!=y)
  {
    x = y;
    y = (x + a / x) / 2;
  }//end of while (x==y)
  return x;
}



/**********************************************************
Function Name:adidentify
Description:AD信号识别
Inputs:  ad
Outputs: None
Notes:   只用了两个电感
***********************************************************/
void adidentify(void)
{

  Pre_Deviation=Deviation;
  if((AD[Left]<10||AD[Right]<10)&&AD[Middle]<70)
  {
    lose_flag=1;
  }
  else
  {
    lose_flag=0;
  }
  
  //弯道直道判断

  if(ABS(AD[Left]-AD[Right])<100)       //式中300可修改
  {
    Curve_Flag=0;
  }
  else
  {
    Curve_Flag=1;
  }
  
  
  if(lose_flag==0)   
  {
    if(Curve_Flag)
    {
      if(AD[Left]-AD[Right]>0)
        Deviation=-(AD[Left]-AD[Right])*(AD[Left]-AD[Right])/100;
      else
        Deviation=(AD[Left]-AD[Right])*(AD[Left]-AD[Right])/100; 
    }
    else
    {
      Deviation=0;
    }
    
  }
  else// (AD[Left]+AD[Right]>80)
  {
    if(AD[Left]>AD[Right])
    {
      Deviation = -10000;
    }
    else
      Deviation = 10000;
  }

  
  // Caculation();
  
  
}
///**********************************************************
//Function Name:adidentify
//Description:AD信号识别
//Inputs:  ad
//Outputs: None
//Notes:   差比和
//**********************************************************/
void Caculation(void)
{

//归一化处理
  

  AD_left=AD[0]+AD[1];
  AD_right=AD[3]+AD[4];
  //AD_sum=AD[0]+AD[1]+AD[2]+AD[3]+AD[4];

  if(AD[4]<40)
  {
  AD[4] = 0;
  }
  else
   AD[4] = AD[4]-40; 
  Pre_Deviation=Deviation;
  
  if(AD[0]<40||AD[4]<40)
  {
  lose_flag=1;
  }
  else
  {
  lose_flag=0;
  }

  //弯道直道判断
  //AD0&AD4是最左边和最右边的电感
  if(ABS(AD[0]-AD[4])<30)       //式中300可修改
  {
    Curve_Flag=0;
  }
  else
  {
    Curve_Flag=1;
  }
  
  
  if(lose_flag==0)   
  {
    if(Curve_Flag)
    {
        Linear_fit=2000000*(sqrt(AD_left)-sqrt(AD_right))/((AD_left+AD_right)*(sqrt(AD_left)+sqrt(AD_right)));
    }
    else
    {
      Linear_fit=0;
    }
    
  }
  else if(AD[0]+AD[4]>40)
  {
  if(AD[0]>AD[4])
  {
    Linear_fit = 500;
  }
  else
    Linear_fit = -500;
    
  }

}
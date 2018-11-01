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
//����ƫ����
float Deviation = 0;
float Pre_Deviation = 0;
float middle_final = 0;
float pre_middle_final = 0;

float Linear_fit;
uint16 AD_left;
uint16 AD_right;
uint8 Curve_Flag=0;
float Z=0;
int flag=0;
//�����־

/**********************************************************
Function Name:sqrt
Description:  
Inputs:  None
Outputs: None
Notes:     ��ƽ����
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
Description:AD�ź�ʶ��
Inputs:  ad
Outputs: None
Notes:   ֻ�����������
***********************************************************/
void adidentify(void)
{
  
  //AD_right=AD[0]+AD[2];
  //AD_left=AD[6]+AD[4];
  //AD_right1=AD[2];
  //AD_left1=AD[4];
 
  int sum=AD[0]+AD[2]+AD[4]+AD[6];
  
  if(sum<=100)
  {
    lose_flag=1;
  }
  else
  {
    lose_flag=0;
  }
  
  //���ֱ���ж�

  if(ABS(AD[2]-AD[4])<150)       //ʽ��300���޸�
  {
    Curve_Flag=0;
  }
  else
  {
    Curve_Flag=1;
  }
  
  
  if(lose_flag==0)   //AD[Left]>10 && AD[Right]>10
  {
    if(AD[0] + AD[6] + AD[2] + AD[4]<=1800 )      //���ƫ��������  ABS(AD[Left]-AD[Right])>150
    {
      if(AD[4]-AD[2]>0)                                            
        Deviation=-10000*(AD[4]-AD[2])/(AD[4]+AD[2]);     //��ת  /100
      else
        Deviation=10000*(AD[2]-AD[4])/(AD[4]+AD[2]);      //��ת   /100
    }
    else  //AD[2]-AD[4]>100||AD[4]-AD[2]>80
    {
      if(AD[4]-AD[2]>0)                                            
        Deviation=-2500*(AD[4]-AD[2])/(AD[4]+AD[2]);     //��ת  /100
      
      else
        //if(AD[2]-AD[4]<=100&&AD[2]-AD[4]>=80)
        Deviation=2500*(AD[2]-AD[4])/(AD[4]+AD[2]);  //��ת   /100
      
    }
//    else
//    {
//      Deviation=0;   //�������  ABS(AD[Left]-AD[Right])<100
//    }
    
  }
  else                                  // lose_flag==1  AD[Left]<10||AD[Right]<10  (AD[Left]+AD[Right]>80)
  {
    
//    if(AD[0]<10&&AD[6]<10)
//    {
//      
//      if(AD[4]>AD[2])
//      {
//        Deviation = -1500;
//      }
//      else
//      {
//        Deviation = 1600;
//      }
//    }
//    else 
//    {
//      if(AD[6]>AD[0])
//      {
//        Deviation = -1700;
//      }
//      else
//        Deviation = 1700;
//    }
    if(Pre_Deviation>0)
      Deviation = 6000;
    else
       Deviation = -6000;
    
  }
//  
//  if(AD[0]<30&&AD[2]<30&&AD[4]<30&&AD[6]<30
//    &&(ABS(AD[0]-AD[6])<5)&&(ABS(AD[2]-AD[4])<5))
//      {  flag++;
//         if(flag==1) Z=Pre_Deviation;
//         Deviation=Pre_Deviation;
//      }
  
//  if(flag>5){flag=0;
//  if(Z>0) Deviation=1600;
//  else Deviation=-1500;
//  }
  Pre_Deviation=Deviation;
  
  // Caculation();
  
  
}
///**********************************************************
//Function Name:adidentify
//Description:AD�ź�ʶ��
//Inputs:  ad
//Outputs: None
//Notes:   ��Ⱥ�
//**********************************************************/
void Caculation(void)
{

//��һ������
  


  //AD_sum=AD[0]+AD[1]+AD[2]+AD[3]+AD[4];

  if(AD[6]<40)
  {
    AD[6] = 0;
  }
  else
    AD[6] = AD[6]-40; 
  Pre_Deviation=Deviation;
  
  if(AD[0]<30||AD[6]<30)
  {
    lose_flag=1;
  }
  else
  {
    lose_flag=0;
  }

  //���ֱ���ж�
  //AD0&AD4������ߺ����ұߵĵ��
  if(ABS(AD[0]-AD[6])<100)       //ʽ��300���޸�
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
  else if(AD[0]+AD[6]>40)
  {
  if(AD[0]>AD[6])
  {
    Linear_fit = 500;
  }
  else
    Linear_fit = -500;
    
  }

}
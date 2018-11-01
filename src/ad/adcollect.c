/*
* File:	sensoroperation.c
* Purpose:	sensor operates
*
* Notes:
*/
#include "common.h"
#include "adcollect.h"
uint16 AD[10];

int AD_max,AD_min;

/**********************************************************
Function Name: AD_Channel
Description: AD通道选择
Inputs:  None
Outputs: None
Notes:
***********************************************************/
uint16 AD_Channel(uint8 Channel)
{
  uint16 Result;
  switch(Channel)
  {
  case 0 : Result = ADC_Once(ADC_CHANNEL_AD4,12);break; //PTB0//L
  //case 1 : Result = ADC_Once(ADC_CHANNEL_AD5,12);break; //PTB1//FL
  case 2 : Result = ADC_Once(ADC_CHANNEL_AD6,12);break;//PTB2//ML
  //case 3 : Result = ADC_Once(ADC_CHANNEL_AD7,12);break;//PTB3//M
  case 4 : Result = ADC_Once(ADC_CHANNEL_AD12,12);break;//PTF4//FM
  //case 5 : Result = ADC_Once(ADC_CHANNEL_AD13,12);break;//PTF5//MR
  case 6 : Result = ADC_Once(ADC_CHANNEL_AD14,12);break; //PTF6//FR
  //case 7 : Result = ADC_Once(ADC_CHANNEL_AD15,12);break; //PTF7//R
  default:break;
  }
  return Result;
}

/**********************************************************
Function Name:adcollect
Description:AD采集
Inputs:  ad
Outputs: None
Notes:
***********************************************************/
void adcollect(void)
{
  //AD[9] = (AD_Channel(9)+AD_Channel(9)+AD_Channel(9)+AD_Channel(9)+AD_Channel(9))/5;
  //AD[8] = (AD_Channel(8)+AD_Channel(8)+AD_Channel(8)+AD_Channel(8)+AD_Channel(6))/5;
  //AD[7] = (AD_Channel(7)+AD_Channel(7)+AD_Channel(7)+AD_Channel(7)+AD_Channel(7))/5;
  AD[6] = (AD_Channel(6)+AD_Channel(6)+AD_Channel(6)+AD_Channel(6)+AD_Channel(6))/5;
  //AD[5] = (AD_Channel(5)+AD_Channel(5)+AD_Channel(5)+AD_Channel(5)+AD_Channel(5))/5;
  AD[4] = (AD_Channel(4)+AD_Channel(4)+AD_Channel(4)+AD_Channel(4)+AD_Channel(4))/5; 
  //AD[3] = (AD_Channel(3)+AD_Channel(3)+AD_Channel(3)+AD_Channel(3)+AD_Channel(3))/5;
  AD[2] = (AD_Channel(2)+AD_Channel(2)+AD_Channel(2)+AD_Channel(2)+AD_Channel(2))/5;
  
  AD[0] = (AD_Channel(0)+AD_Channel(0)+AD_Channel(0)+AD_Channel(0)+AD_Channel(0))/5-76;
  AD[1] = (AD_Channel(1)+AD_Channel(1)+AD_Channel(1)+AD_Channel(1)+AD_Channel(1))/5;
  //可以考虑加滤波算法
  if(AD[0]>5000)
  {
    AD[0]=0;
  }
  
//  AD_max=800;
//  AD_min=0;
//  AD[0]=AD[0]*(AD[0]-AD_min)/(AD_max-AD_min);
//  AD[2]=AD[2]*(AD[2]-AD_min)/(AD_max-AD_min);
//  AD[4]=AD[4]*(AD[4]-AD_min)/(AD_max-AD_min);
//  AD[6]=AD[6]*(AD[6]-AD_min)/(AD_max-AD_min);
  
}
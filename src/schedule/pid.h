/*
* File:	pid.h
* Purpose:	pid control
*
* Notes:
*/

#ifndef __PID_H__
#define __PID_H__

/******************************************************************************/
#define VV_MAX 999 		 //�ٶ�PID���������ֵ
#define VV_MIN 0	    	 //�ٶ�PID��������Сֵ
#define VV_DEADLINE 0	         //�ٶ�PID������������Χ

//struct
typedef struct PID
{
  int16 vi_Ref;	         //�ٶ�PID���ٶ��趨ֵ
  int16 vi_FeedBack;       //�ٶ�PID���ٶȷ���ֵ
  int16 vi_PreError;	 //�ٶ�PID���ٶ����,vi_Ref - vi_FeedBack
  int16 vi_PreDerror;	 //�ٶ�PID��ǰһ�Σ��ٶ����֮�d_error-PreDerror;
  int16 v_Kp;		 //����ϵ����Kp = Kp
  int16 v_Ki;		 //����ϵ����Ki = Kp * ( T / Ti )
  int16 v_Kd;		 //΢��ϵ����Kd = KP * Td * T
  int16 vl_PreU;		 //PID���ֵ
}PID;

// Function prototypes
void PIDInit(void);
int16 V_PIDCalc(PID *pp);

//extern
extern PID sPID;

/******************************************************************************/
#endif /* __SCHEDULE_H__ */
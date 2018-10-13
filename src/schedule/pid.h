/*
* File:	pid.h
* Purpose:	pid control
*
* Notes:
*/

#ifndef __PID_H__
#define __PID_H__

/******************************************************************************/
#define VV_MAX 999 		 //速度PID，调节最大值
#define VV_MIN 0	    	 //速度PID，调节最小值
#define VV_DEADLINE 0	         //速度PID，设置死区范围

//struct
typedef struct PID
{
  int16 vi_Ref;	         //速度PID，速度设定值
  int16 vi_FeedBack;       //速度PID，速度反馈值
  int16 vi_PreError;	 //速度PID，速度误差,vi_Ref - vi_FeedBack
  int16 vi_PreDerror;	 //速度PID，前一次，速度误差之差，d_error-PreDerror;
  int16 v_Kp;		 //比例系数，Kp = Kp
  int16 v_Ki;		 //积分系数，Ki = Kp * ( T / Ti )
  int16 v_Kd;		 //微分系数，Kd = KP * Td * T
  int16 vl_PreU;		 //PID输出值
}PID;

// Function prototypes
void PIDInit(void);
int16 V_PIDCalc(PID *pp);

//extern
extern PID sPID;

/******************************************************************************/
#endif /* __SCHEDULE_H__ */
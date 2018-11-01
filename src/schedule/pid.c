/*
 * File:	pid.c
 * Purpose:
 *
 * Notes:
 */
#include "common.h"
#include "pid.h"

/*
function name:  PIDInit
parameters:     none
author:
date:           2012-6-27
description:    initialize PID values
*/
PID sPID;

int16 error1;
int16 errormax = 0;
int16 risetime =0;
int   riseflag = 0;

void PIDInit(void)
{
    sPID.vi_Ref = 0;	 //0
    sPID.vi_FeedBack = 0 ;

    sPID.vi_PreError = 0 ;
    sPID.vi_PreDerror = 0 ;

    sPID.v_Kp = 15;
    sPID.v_Ki = 7;
    sPID.v_Kd = 1;

    sPID.vl_PreU = 0;
}

/*
function name:  V_PIDCalc
parameters:     none
author:
date:           2012-6-27
description:    PID control
*/
int16 V_PIDCalc(PID *pp)
{
    int16  error,d_error,dd_error;

    error = pp->vi_Ref - pp->vi_FeedBack;
    
    error1=error;
    if(error1>0 && riseflag ==0)
    {
      risetime++;
    }   
    else
    {
      riseflag =1;
    }
    if (sPID.vi_Ref==0)
    {
      riseflag=0;
    }
    if(error1<errormax)
      errormax = error1;
    
    d_error = error - pp->vi_PreError;
    dd_error = d_error - pp->vi_PreDerror;

    pp->vi_PreError = error;
    pp->vi_PreDerror = d_error;

    if( ( error < VV_DEADLINE ) && ( error > -VV_DEADLINE ) )
    {
        ;
    }
    else
    {
        pp->vl_PreU += (pp -> v_Kp * d_error + pp -> v_Ki * error + pp->v_Kd*dd_error);
    }

    if( pp->vl_PreU >= VV_MAX )
    {
        pp->vl_PreU = VV_MAX;
    }
    else if( pp->vl_PreU <= VV_MIN )
    {
        pp->vl_PreU = VV_MIN;
    }

     return (pp->vl_PreU);
}

/******************************************************************************/

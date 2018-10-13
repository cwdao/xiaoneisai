/*
 * File:	schedule.h
 * Purpose:	schedule
 *
 * Notes:
 */

#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__
/******************************************************************************/
typedef uint8   INT8U;
typedef int8    INT8S;
typedef uint16  INT16U;
typedef int16   INT16S;
typedef uint32  INT32U;
typedef int32   INT32S;
typedef uint64  INT64U;
typedef int64   INT64S;

/*----------------------- D E C L A R A T I O N ------------------------------*/

extern int16 g_countervalue;
extern uint16 g_time;
extern uint8 Stop_Flag;
extern uint16 servotest;
extern uint16 Motor_Test;
extern uint8 lose_flag;

// Function prototypes
void ScheduleInit(void);
void pit0_isr(void);
void Car_Run_openloop(void);
void Car_Run_closedloop(void);
void Car_Turn(void);
void Magnet_detect(void);
void JM_STATUS_init(void);

/******************************************************************************/

#endif /* __SCHEDULE_H__ */





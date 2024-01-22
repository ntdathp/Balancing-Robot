#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include <stdint.h>
#include "pid.h"
#include "tim.h"
typedef struct
{
	uint16_t counter;
	uint16_t rounds;
	float vel;
	float o_vel;
	float o_vel2;
	float velocity;
	float position;
    float setPoint;
} Motor_t;

extern void MotorReset(Motor_t *tmotor);
extern void MotorSetDuty1(int nDuty);
extern void MotorSetDuty2(int nDuty);
extern void ReadEncoder(Motor_t *tmotor, TIM_HandleTypeDef *htim);
extern float MotorTuningVelocity(PID_CONTROL_t *PIDControl,Motor_t * tmotor,float vel);
extern float MotorTuningPosition(PID_CONTROL_t * PIDControl,Motor_t * tmotor, float pos);

#endif /* INC_MOTOR_H_ */

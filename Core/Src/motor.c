#include "motor.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "tim.h"
#include "pid.h"

#define PPR 1320;
#define RTD 360/1320;

void MotorReset(Motor_t *tmotor)
{
	tmotor->counter = 0;


	tmotor->o_vel = 0;
	tmotor->o_vel2 = 0;
	tmotor->vel = 0;
	tmotor->velocity = 0;

	tmotor->rounds = 0;
	tmotor->position = 0;
}

//duty cycle of motor
void MotorSetDuty1(int nDuty)
{
	if(nDuty == 0){
		htim3.Instance->CCR1 = 0;
		htim3.Instance->CCR2 = 0;
	}
	else if(nDuty > 0){
		htim3.Instance->CCR2 = nDuty+500;
		htim2.Instance->CCR1 = 0;
	}
	else if(nDuty < 0){
		htim3.Instance->CCR2 = 0;
		htim3.Instance->CCR1 = abs(nDuty-500);
	}

}

void MotorSetDuty2(int nDuty)
{
	if(nDuty == 0){
		htim3.Instance->CCR3 = 0;
		htim3.Instance->CCR4 = 0;
	}
	else if(nDuty>0){
		htim3.Instance->CCR4 = nDuty;
		htim3.Instance->CCR3 = 0;
	}
	else if(nDuty<0){
		htim3.Instance->CCR4 = 0;
		htim3.Instance->CCR3 = abs(nDuty);
	}

}

// sample 10ms
void ReadEncoder(Motor_t * tmotor, TIM_HandleTypeDef *htim){
			tmotor->counter = htim->Instance->CNT;

			tmotor->rounds += tmotor->counter/PPR;


			int16_t temp_data = tmotor->counter;


			tmotor->vel = (float)temp_data *100. *60. / PPR ; // RPM


			tmotor->position += (float)temp_data * RTD; //deg

			//LPF

			tmotor->velocity = 0.7*tmotor->vel + 0.2*tmotor->o_vel + 0.1*tmotor->o_vel2;

			tmotor->o_vel = tmotor->vel;
			tmotor->o_vel2 = tmotor->o_vel;

			htim->Instance->CNT = 0;
}

//Turning
float MotorTuningVelocity(PID_CONTROL_t * PIDControl,Motor_t * tmotor,float velocity)
{
    float SetPoint = velocity;
    float Input = tmotor->velocity;
    float g_nDutyCycle = PIDCompute(PIDControl, SetPoint,Input, 0.01f);
    return g_nDutyCycle;
}
float MotorTuningPosition(PID_CONTROL_t *PIDControl, Motor_t * tmotor, float position)
{
    float SetPoint = position;
    float Input=tmotor->position;
    float g_nDutyCycle = PIDCompute(PIDControl, SetPoint,Input, 0.03f);
    return g_nDutyCycle;
}

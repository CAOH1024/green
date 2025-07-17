#include "PID.h"

float abs_limit(float value, float ABS_MAX)  
{
	if(value > ABS_MAX)
		value = ABS_MAX;

	if(value< -ABS_MAX)
		value = -ABS_MAX;
	return value;
}


//???????,????????????
float PID_Position_Calc(PID *pid, float Target_val, float Actual_val)  //???PID
{   

	pid->Error = Target_val - Actual_val;      //?pid P?????????? ????=???-???
	pid->SumError += pid->Error;                 //?pid I?????????? ??????????,????
	pid->DError = pid->Error - pid->LastError;   //?pid D????? ???-????

	pid->output =   pid->Kp* pid->Error +        
					abs_limit( pid->Ki* pid->SumError, pid->Integralmax ) +   
					pid->Kd* pid->DError ;  
								
   pid->LastError = pid->Error; //????
   
  //???????,???????????outputmax????
	if(pid->output > pid->outputmax )  pid->output = pid->outputmax; 
	if(pid->output < - pid->outputmax )  pid->output = -pid->outputmax;
	
	return pid->output ;   //???pwm?
}

//PID???
void PID_Init(PID *pid, float Kp , float Ki , float Kd , float Limit_value)  
{  
	pid->Kp= Kp;
	pid->Ki= Ki;
	pid->Kd= Kd;
	
	pid->PrevError =pid->LastError = pid->Error =pid->SumError= pid->output =  0; 
	pid->Integralmax = pid->outputmax  = Limit_value;
}  

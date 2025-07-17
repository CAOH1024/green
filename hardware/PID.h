#ifndef __PID_H
#define __PID_H

typedef struct PID {
		float  Kp;         //  Proportional Const  P??
		float  Ki;           //  Integral Const      I??
		float  Kd;         //  Derivative Const    D??
		
		float  PrevError ;          //  Error[-2]  
		float  LastError;          //  Error[-1]  
		float  Error;              //  Error[0 ]  
		float  DError;            //pid->Error - pid->LastError	
		float  SumError;           //  Sums of Errors  
		
		float  output;
		
		float  Integralmax;      //???????
		float  outputmax;        //???????
} PID;

float abs_limit(float value, float ABS_MAX);
float PID_Position_Calc(PID *pid, float Target_val, float Actual_val);
void PID_Init(PID *pid, float Kp , float Ki , float Kd , float Limit_value);


#endif

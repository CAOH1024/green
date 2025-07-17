#include "main.h"

//-------------------------------

#define X_Kp 1.0f
#define X_Ki 0.1f
#define X_Kd 0.01f
#define X_Limit 100.0f
uint16_t X_CCR = 1500;

//-------------------------------

#define Y_Kp 1.0f
#define Y_Ki 0.1f
#define Y_Kd 0.01f
#define Y_Limit 100.0f
uint16_t Y_CCR = 1500;

//-------------------------------

uint32_t count;

int main(void){

	Serial_Init();
	PWM_LED_Init();
	PID_Init(&X_Pos, X_Kp, X_Ki, X_Kd, X_Limit);
	PID_Init(&Y_Pos, Y_Kp, Y_Ki, Y_Kd, Y_Limit);

	while(1)
	{
		if(Serial_GetFlag()){
			X_CCR += PID_Position_Calc(&X_Pos, 0, Serial_RXPacket[0]);
			Y_CCR += PID_Position_Calc(&Y_Pos, 0, Serial_RXPacket[2]);
		}
		TIM_SetCompare2(TIM2, X_CCR);
		TIM_SetCompare3(TIM2, Y_CCR);
	}
}

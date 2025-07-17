#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWMLED.h"
#include "PID.h"

int main(void){
	PWM_LED_Init();
	while(1)
	{
		Delay_s(1);
		Set_Servo_Angle(1, 0);
		Delay_s(1);
		Set_Servo_Angle(1, 0.5);
		Delay_s(1);
		Set_Servo_Angle(1, 1);
	}
}

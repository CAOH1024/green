#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWMLED.h"

int main(){
	PWM_LED_Init();
	Set_PWMCCR(0);
	while(1)
	{
		
	}
}

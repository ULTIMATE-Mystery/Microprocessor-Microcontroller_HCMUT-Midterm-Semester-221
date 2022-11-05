
#include "timer_interrupt.h"

//flag is on after a specific duration
int timer_flag = 0;

//timer_counter to determine if flag is on or not
int timer_counter = 0;

//set timer_counter and reset flag
void setTimer(int duration){
	timer_counter = duration / TIMER_CYCLE;
	timer_flag = 0;
}

//decrement timer_counter and check if flag is on or not
void timerRun(){
	if (timer_counter > 0){
		timer_counter--;
		if (timer_counter <= 0){
			timer_flag = 1;
		}
	}
}


int debugLED_timerCounter = 50;	//timer counter for DEBUG_LED
//timer callback
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		timerRun();
		buttonReading();
		debugLED_timerCounter--;
		//toggle DEBUG_LED
		if (debugLED_timerCounter <= 0){
			debugLED_timerCounter = 50;
			HAL_GPIO_TogglePin(GPIOA, DEBUG_LED_Pin);
		}
	}
}

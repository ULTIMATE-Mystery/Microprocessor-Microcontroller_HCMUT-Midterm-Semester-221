/*
 * software_timer.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Minh Duc Quach
 */

#include "software_timer.h"

//flag is on after a specific duration
int timerFlag = 0;

//counter to determine if flag is on or not
int counter = 0;

//set counter and reset flag
void setTimer(int duration){
	counter = duration / TICK;
	timerFlag = 0;
}

//decrement counter and check if flag is on or not
void timerRun(){
	if (counter > 0){
		counter--;
		if (counter <= 0){
			timerFlag = 1;
		}
	}
}

int cnt = 50;	//counter for DEBUG_LED

//timer callback
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		timerRun();
		button_reading();
		cnt--;
		//toggle DEBUG_LED
		if (cnt <= 0){
			cnt = 50;
			HAL_GPIO_TogglePin(GPIOA, DEBUG_LED_Pin);
		}
	}
}

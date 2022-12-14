
#include "display.h"

int led_buffer[NO_OF_7SEG] = {0};	//buffer for 7 SEG LED

//turn off 7 SEG LED
void clear7SEG(){
	HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
	                          |SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_SET);
}

//display counter value
void display7SEG(int counter){
	if (counter == 0){
		clear7SEG();
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
			                          |SEG4_Pin|SEG5_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 1){
		clear7SEG();
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin|SEG2_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 2){
		clear7SEG();
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG3_Pin
			                          |SEG4_Pin|SEG6_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 3){
		clear7SEG();
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
						     	 	  |SEG6_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 4){
		clear7SEG();
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin|SEG2_Pin|SEG5_Pin
						     	 	  |SEG6_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 5){
		clear7SEG();
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG2_Pin|SEG3_Pin
						     	 	  |SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 6){
		clear7SEG();
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG2_Pin|SEG3_Pin
									  |SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 7){
		clear7SEG();
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 8){
		clear7SEG();
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
						              |SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 9){
		clear7SEG();
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
						              |SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
	}
}

//reset buffer value to 0 and then display
void resetBuffer(){
	led_buffer[0] = 0;
	display7SEG(led_buffer[0]);
}

//increment buffer value by 1 unit and then display
void incBuffer(int value){
	led_buffer[0] += value;
	display7SEG(led_buffer[0]);
}

//decrement buffer value by 1 unit and then display
void decBuffer(int value){
	led_buffer[0] -= value;
	display7SEG(led_buffer[0]);
}

//update buffer value with a specific number and then display
void updateBuffer(int value){
	led_buffer[0] = value;
	display7SEG(led_buffer[0]);
}

//return current buffer value
int bufferValue(){
	return led_buffer[0];
}

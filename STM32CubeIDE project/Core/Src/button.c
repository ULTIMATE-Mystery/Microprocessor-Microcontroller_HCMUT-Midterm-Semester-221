
#include "button.h"

//filtered button states
static GPIO_PinState buttonBuffer[NO_OF_BUTTON];

//button filter
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTON];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTON];
static GPIO_PinState debounceButtonBuffer3[NO_OF_BUTTON];

//time out value for long pressed case
int normalPressedTimeOut[NO_OF_BUTTON];

//flag is on when button is pressed and released immediately (normal pressed)
int buttonNormalFlag[NO_OF_BUTTON];

//flag is on when button is pressed and hold for 3 seconds (long pressed for 3 seconds)
int buttonLongFlag[NO_OF_BUTTON];

//flag used for increment counter by 1 unit
int flagForLongPressed[NO_OF_BUTTON] = {0, 0, 0};

//button arrays
GPIO_TypeDef* port[NO_OF_BUTTON] = {RESET_GPIO_Port, INC_GPIO_Port, DEC_GPIO_Port};
uint16_t pin[NO_OF_BUTTON] = {RESET_Pin, INC_Pin, DEC_Pin};

void buttonReading(){
	for(int i = 0; i < NO_OF_BUTTON; i ++){
		//filtering
		debounceButtonBuffer3[i] = debounceButtonBuffer2[i];
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(port[i], pin[i]);
		if(debounceButtonBuffer3[i] == debounceButtonBuffer2[i] && debounceButtonBuffer2[i] == debounceButtonBuffer1[i]){
			if (buttonBuffer[i] != debounceButtonBuffer1[i]){	//a change in state occured
				buttonBuffer[i] = debounceButtonBuffer1[i];
				if (buttonBuffer[i] == BUTTON_PRESSED){		//normal pressed
					if (flagForLongPressed[i] == 0){
						buttonNormalFlag[i] = 1;
						normalPressedTimeOut[i] = LONG_PRESSED_TIME;
					}
					else normalPressedTimeOut[i] = 100;
				}
				else flagForLongPressed[i] = 0;
			}
			else {
				normalPressedTimeOut[i]--;
				if (normalPressedTimeOut[i] <= 0 && debounceButtonBuffer1[i] == BUTTON_PRESSED){	//long pressed
					normalPressedTimeOut[i] = 0;
					buttonLongFlag[i] = 1;
					buttonBuffer[i] = BUTTON_RELEASED;
					flagForLongPressed[i] = 1;
				}
				else if (normalPressedTimeOut[i] <= 0) normalPressedTimeOut[i] = 0;
			}
		}
	}
}

//if button is pressed, return 1, else return 0
int isButtonNormalPressed(int index){
	if(index >= NO_OF_BUTTON) return 0;
	if (buttonNormalFlag[index] == 1){
		buttonNormalFlag[index] = 0;
		return 1;
	}
	return 0;
}

//if button is long pressed for 3 seconds, return 1, else return 0
int isButtonLongPressed(int index){
	if(index >= NO_OF_BUTTON) return 0;
	if (buttonLongFlag[index] == 1){
		buttonLongFlag[index] = 0;
		return 1;
	}
	return 0;
}

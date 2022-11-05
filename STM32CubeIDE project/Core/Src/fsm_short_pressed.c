/*
 * fsm_automatic.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Minh Duc Quach
 */

#include "fsm_short_pressed.h"

void fsm_short_pressed_run(){
	//isButtonPressed(0): RESET, (1): INC, (2): DEC. Same rule applies to isButtonPressed3s()
	switch(status){
	case INIT:
		//switch to RESET state
		clearEN();
		resetBuffer();
		openEN();
		status = COUNTER_RESET;
		setTimer(10000);	//timeout 10s
		break;
	case COUNTER_RESET:
		//10s passed, do nothing
		if (timerFlag == 1){
			clear7SEGs();
			resetBuffer();
			status = COUNTER_RESET;
			setTimer(1000);
		}
		//pressed RESET, do nothing
		if (isButtonPressed(0)){
			clear7SEGs();
			resetBuffer();
			status = COUNTER_RESET;
			setTimer(10000);
		}
		//pressed INC, increment counter and then switch to INC
		if (isButtonPressed(1)){
			clear7SEGs();
			increaseBuffer(1);
			status = COUNTER_INC;
			setTimer(10000);
		}
		//pressed DEC, decrement counter and then switch to DEC
		if (isButtonPressed(2)){
			clear7SEGs();
			updateBuffer(9);
			status = COUNTER_DEC;
			setTimer(10000);
		}
		break;
	case COUNTER_INC:
		//10s passed, decrement counter (if counter != 0) and then switch to DEC_AUTO
		if (timerFlag == 1){
			clear7SEGs();
			if (bufferValue() != 0) decreaseBuffer(1);
			else resetBuffer();
			status = COUNTER_DEC_AUTO;
			setTimer(1000);
		}
		//pressed RESET, reset counter and then switch to RESET
		if (isButtonPressed(0)){
			clear7SEGs();
			resetBuffer();
			status = COUNTER_RESET;
			setTimer(10000);
		}
		//pressed INC, increment counter
		if (isButtonPressed(1)){
			clear7SEGs();
			if (bufferValue() == 9) resetBuffer();
			else increaseBuffer(1);
			status = COUNTER_INC;
			setTimer(10000);
		}
		//pressed DEC, decrement counter and then switch to DEC
		if (isButtonPressed(2)){
			clear7SEGs();
			if (bufferValue() == 0) updateBuffer(9);
			else decreaseBuffer(1);
			status = COUNTER_DEC;
			setTimer(10000);
		}
		//pressed INC for 3 seconds, increment counter and switch to COUNTER_INC_LONG
		if (isButtonPressed3s(1)){
			clear7SEGs();
			if (bufferValue() == 9) resetBuffer();
			else increaseBuffer(1);
			status = COUNTER_INC_LONG;
		}
		break;
	case COUNTER_DEC:
		//10s passed, decrement counter (if != 0) and then switch to DEC_AUTO
		if (timerFlag == 1){
			clear7SEGs();
			if (bufferValue() == 0){
				resetBuffer();
			}
			else{
				decreaseBuffer(1);
			}
			status = COUNTER_DEC_AUTO;
			setTimer(1000);
		}
		//pressed RESET, reset counter and then switch to RESET
		if (isButtonPressed(0)){
			clear7SEGs();
			resetBuffer();
			status = COUNTER_RESET;
			setTimer(10000);
		}
		//pressed INC, increment counter and then switch to INC
		if (isButtonPressed(1)){
			clear7SEGs();
			if (bufferValue() == 9) resetBuffer();
			else increaseBuffer(1);
			status = COUNTER_INC;
			setTimer(10000);
		}
		//pressed DEC, decrement counter
		if (isButtonPressed(2)){
			clear7SEGs();
			if (bufferValue() == 0) updateBuffer(9);
			else decreaseBuffer(1);
			status = COUNTER_DEC;
			setTimer(10000);
		}
		//pressed DEC for 3 seconds, decrement counter and switch to COUNTER_DEC_LONG
		if (isButtonPressed3s(2)){
			clear7SEGs();
			if (bufferValue() == 0) updateBuffer(9);
			else decreaseBuffer(1);
			status = COUNTER_DEC_LONG;
		}
		break;
	default:
		break;
	}
}



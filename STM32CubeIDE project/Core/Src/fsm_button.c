/*
 * fsm_button.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Phạm Duy Quang
 */

#include "fsm_button.h"

void fsm_normal_pressed(){
	//isButtonNormalPressed(0): RESET, (1): INC, (2): DEC. Same rule applies to isButtonLongPressed()
	switch(status){
	case INIT:
		//switch to RESET state
		resetBuffer();
		status = COUNTER_RESET;
		setTimer(10000);	//timeout 10s
		break;
	case COUNTER_RESET:
		//10s passed, do nothing
		if (timer_flag == 1){
			clear7SEG();
			resetBuffer();
			status = COUNTER_RESET;
			setTimer(1000);
		}
		//pressed RESET, do nothing
		if (isButtonNormalPressed(0)){
			clear7SEG();
			resetBuffer();
			status = COUNTER_RESET;
			setTimer(10000);
		}
		//pressed INC, increment counter and then switch to INC
		if (isButtonNormalPressed(1)){
			clear7SEG();
			incBuffer(1);
			status = COUNTER_INC_NORMAL;
			setTimer(10000);
		}
		//pressed DEC, decrement counter and then switch to DEC
		if (isButtonNormalPressed(2)){
			clear7SEG();
			updateBuffer(9);
			status = COUNTER_DEC_NORMAL;
			setTimer(10000);
		}
		break;
	case COUNTER_INC_NORMAL:
		//10s passed, decrement counter (if counter != 0) and then switch to DEC_AUTO
		if (timer_flag == 1){
			clear7SEG();
			if (bufferValue() != 0) decBuffer(1);
			else resetBuffer();
			status = COUNTER_AUTO_DEC;
			setTimer(1000);
		}
		//pressed RESET, reset counter and then switch to RESET
		if (isButtonNormalPressed(0)){
			clear7SEG();
			resetBuffer();
			status = COUNTER_RESET;
			setTimer(10000);
		}
		//pressed INC, increment counter
		if (isButtonNormalPressed(1)){
			clear7SEG();
			if (bufferValue() == 9) resetBuffer();
			else incBuffer(1);
			status = COUNTER_INC_NORMAL;
			setTimer(10000);
		}
		//pressed DEC, decrement counter and then switch to DEC
		if (isButtonNormalPressed(2)){
			clear7SEG();
			if (bufferValue() == 0) updateBuffer(9);
			else decBuffer(1);
			status = COUNTER_DEC_NORMAL;
			setTimer(10000);
		}
		//pressed INC for 3 seconds, increment counter and switch to COUNTER_INC_LONG
		if (isButtonLongPressed(1)){
			clear7SEG();
			if (bufferValue() == 9) resetBuffer();
			else incBuffer(1);
			status = COUNTER_INC_LONG;
		}
		break;
	case COUNTER_DEC_NORMAL:
		//10s passed, decrement counter (if != 0) and then switch to DEC_AUTO
		if (timer_flag == 1){
			clear7SEG();
			if (bufferValue() == 0){
				resetBuffer();
			}
			else{
				decBuffer(1);
			}
			status = COUNTER_AUTO_DEC;
			setTimer(1000);
		}
		//pressed RESET, reset counter and then switch to RESET
		if (isButtonNormalPressed(0)){
			clear7SEG();
			resetBuffer();
			status = COUNTER_RESET;
			setTimer(10000);
		}
		//pressed INC, increment counter and then switch to INC
		if (isButtonNormalPressed(1)){
			clear7SEG();
			if (bufferValue() == 9) resetBuffer();
			else incBuffer(1);
			status = COUNTER_INC_NORMAL;
			setTimer(10000);
		}
		//pressed DEC, decrement counter
		if (isButtonNormalPressed(2)){
			clear7SEG();
			if (bufferValue() == 0) updateBuffer(9);
			else decBuffer(1);
			status = COUNTER_DEC_NORMAL;
			setTimer(10000);
		}
		//pressed DEC for 3 seconds, decrement counter and switch to COUNTER_DEC_LONG
		if (isButtonLongPressed(2)){
			clear7SEG();
			if (bufferValue() == 0) updateBuffer(9);
			else decBuffer(1);
			status = COUNTER_DEC_LONG;
		}
		break;
	default:
		break;
	}
}

void fsm_long_pressed(){
	//isButtonNormalPressed(0): RESET, (1): INC, (2): DEC. Same rule applies to isButtonLongPressed()
	switch(status){
	case COUNTER_INC_LONG:
		//keep pressing INC button, increment counter every 1 second
		if (isButtonLongPressed(1)){
			clear7SEG();
			if (bufferValue() == 9) resetBuffer();
			else incBuffer(1);
			status = COUNTER_INC_LONG;
		}
		//release INC button, switch to INC
		if (isButtonNormalPressed(1) == 0){
			status = COUNTER_INC_NORMAL;
		}
		break;
	case COUNTER_DEC_LONG:
		//keep pressing DEC button, decrement counter every 1 second
		if (isButtonLongPressed(2)){
			clear7SEG();
			if (bufferValue() == 0) updateBuffer(9);
			else decBuffer(1);
			status = COUNTER_DEC_LONG;
		}
		//release DEC button, switch to DEC
		if (isButtonNormalPressed(2) == 0){
			status = COUNTER_DEC_NORMAL;
		}
		break;
	default:
		break;
	}
}

void fsm_auto_dec(){
	switch(status){
	//isButtonNormalPressed(0): RESET, (1): INC, (2): DEC. Same rule applies to isButtonLongPressed()
	case COUNTER_AUTO_DEC:
		//decrement counter every 1 second
		if (timer_flag == 1){
			clear7SEG();
			if (bufferValue() == 0){
				resetBuffer();
			}
			else{
				decBuffer(1);
			}
			status = COUNTER_AUTO_DEC;
			setTimer(1000);
		}
		//switch to RESET when buffer value = 0
		if (bufferValue() == 0){
			status = COUNTER_RESET;
			setTimer(10000);
		}
		//pressed RESET, reset counter and then switch to RESET
		if (isButtonNormalPressed(0)){
			clear7SEG();
			resetBuffer();
			status = COUNTER_RESET;
			setTimer(10000);
		}
		//pressed INC, increment counter and then switch to INC
		if (isButtonNormalPressed(1)){
			clear7SEG();
			if (bufferValue() == 9) resetBuffer();
			else incBuffer(1);
			status = COUNTER_INC_NORMAL;
			setTimer(10000);
		}
		//pressed DEC, decrement counter and then switch to DEC
		if (isButtonNormalPressed(2)){
			clear7SEG();
			if (bufferValue() == 0) updateBuffer(9);
			else decBuffer(1);
			status = COUNTER_DEC_NORMAL;
			setTimer(10000);
		}
		break;
	default:
		break;
	}
}

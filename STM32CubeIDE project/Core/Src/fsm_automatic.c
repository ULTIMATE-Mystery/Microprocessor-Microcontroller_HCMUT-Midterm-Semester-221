
#include "fsm_automatic.h"

void fsm_automatic_run(){
	switch(status){
	//isButtonNormalPressed(0): RESET, (1): INC, (2): DEC. Same rule applies to isButtonPressed3s()
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

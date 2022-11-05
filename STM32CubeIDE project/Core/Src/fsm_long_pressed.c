
#include "fsm_long_pressed.h"

void fsm_long_pressed_run(){
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


#ifndef INC_TIMER_INTERRUPT_H_
#define INC_TIMER_INTERRUPT_H_

#include "global.h"

#define TIMER_CYCLE		10
#define SECOND			1000

extern int timer_flag;

void setTimer(int);

void timerRun();

#endif /* INC_TIMER_INTERRUPT_H_ */


#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "timer_interrupt.h"
#include "fsm_automatic.h"
#include "fsm_long_pressed.h"
#include "fsm_short_pressed.h"
#include "button.h"
#include "display.h"
#include "main.h"

extern int status;

#define	INIT				0
#define COUNTER_RESET		1
#define COUNTER_INC_NORMAL	2
#define COUNTER_DEC_NORMAL	3

#define COUNTER_INC_LONG	12
#define COUNTER_DEC_LONG	13

#define COUNTER_AUTO_DEC	23

#endif /* INC_GLOBAL_H_ */

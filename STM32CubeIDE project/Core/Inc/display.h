
#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "global.h"

#define NO_OF_7SEG	1
#define TIMER_7SEG	10

void clear7SEG();

void display7SEG(int);

int bufferValue();
void updateBuffer(int);
void resetBuffer();
void incBuffer(int);
void decBuffer(int);

#endif /* INC_DISPLAY_H_ */

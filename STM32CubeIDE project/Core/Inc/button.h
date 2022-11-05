
#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "global.h"

#define NO_OF_BUTTON			3
#define BUTTON_PRESSED			GPIO_PIN_RESET
#define BUTTON_RELEASED			GPIO_PIN_SET

#define	BETWEEN_PRESSED_TIME	30
#define LONG_PRESSED_TIME		300

void buttonReading();
int isButtonNormalPressed(int);
int isButtonLongPressed(int);

#endif /* INC_BUTTON_H_ */

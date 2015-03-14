#include <Arduino.h>
#include "enum_test.h"
#include "PIN_DEFS.h"

void clearLEDs() {
	digitalWrite(RED_LED, LOW);
	digitalWrite(GREEN_LED, LOW);
	digitalWrite(BLUE_LED, LOW);
}

void setStatus(STATUS_CODE status) 
{
	clearLEDs();

	switch (status) {
		case OK:
			digitalWrite(GREEN_LED, HIGH);
			break;
		case ERR:
			digitalWrite(RED_LED, HIGH);
			break;
		case WAIT:
			digitalWrite(BLUE_LED, HIGH);
			break;
	}
}
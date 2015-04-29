#include "relic_outbox.h"
#include <Arduino.h>

static Outbox outbox;

void sendMail(coapMsg * msg) {} 

void deleteMail(MailOutSlot * mail) {
	mail->isFree = true;
}

void resend(MailOutSlot * mail) {
	sendMail(&(mail->message));
	mail->interval *= 2;
}

void checkTimeoutsAndResend() {
	int i;
	unsigned long currentTime = millis();
	for (i = 0; i < OUTBOXSIZE; i++) {
		if (currentTime - outbox.mail[i].timestamp > outbox.mail[i].interval) {
			resend(&(outbox.mail[i]));
			if (outbox.mail[i].interval > MESSAGE_TIMEOUT) { 
				deleteMail(outbox.mail + i); 
			}
		}
	}
}

bool _OUTBOX_empty() {
	int i;
	for (i = 0; i < OUTBOXSIZE; i++) {
		if (!outbox.mail[i].isFree) { return false; }
	}
	return true;
}

void _OUTBOX_newMessage(coapMsg * msg) {}

Outbox * initOutbox(unsigned int remotePort) {
	//outbox.remoteServer = remoteServer;
	outbox.remotePort = remotePort;
	outbox.checkTimeoutsAndResend = &checkTimeoutsAndResend;
	outbox.empty = &_OUTBOX_empty;
	outbox.newMessage = &_OUTBOX_newMessage;

	return &outbox;
}
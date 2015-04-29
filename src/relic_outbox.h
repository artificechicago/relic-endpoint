#ifndef __RELIC_OUTBOX_H__
#define __RELIC_OUTBOX_H__

#define OUTBOXSIZE 3
#define MESSAGE_TIMEOUT 60000 //timeout after one minute of attempts
#include "CoAP.h"
#include "relic_mailer.h"

typedef struct _RELIC_MAIL_OUTBOX_SLOT_ {
	coapMsg message;
	bool isFree;
	unsigned long timestamp;
	unsigned long interval;
} MailOutSlot;

typedef struct _RELIC_OUTBOX_ {
	MailOutSlot mail[OUTBOXSIZE];
	//IPAddress * remoteServer;
	unsigned int remotePort;
	void (*checkTimeoutsAndResend) ();
	bool (*empty)();
	void (*newMessage)(coapMsg * msg);
} Outbox;

#ifdef __cplusplus
extern "C"{
#endif
	Outbox * initOutbox(unsigned int remotePort);
#ifdef __cplusplus
}
#endif //extern"C"
#endif
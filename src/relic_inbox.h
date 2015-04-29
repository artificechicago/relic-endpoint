#ifndef __RELIC_INBOX_H__
#define __RELIC_INBOX_H__

#define INBOXSIZE 3
#include "CoAP.h"
#include "relic_outbox.h"
#include "relic_mailer.h"

typedef struct _RELIC_MAIL_INBOX_SLOT_ {
	coapMsg message;
	bool isFree;
} MailInSlot;

typedef struct _RELIC_MAIL_INBOX_ {
	MailInSlot mail[INBOXSIZE];
	Outbox * outbox;
	void (*processNextMessage)();
	bool (*empty)();
} Inbox;

#ifdef __cplusplus
extern "C"{
#endif
	Inbox * initInbox(Outbox * outbox);
#ifdef __cplusplus
}
#endif //extern "C"

#endif // Header guard
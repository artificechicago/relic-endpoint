#ifndef __RELIC_MAILBOX_H__
#define __RELIC_MAILBOX_H__

#include "CoAP.h"

typedef struct _RELIC_MAIL_SLOT_ {
	coapMsg message;
	bool isFree;
} MailSlot;

typedef struct _RELIC_MAILBOX_ {
	
}

#endif
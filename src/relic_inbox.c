#include "relic_inbox.h"

static Inbox inbox;

bool _INBOX_empty() {
	return false;
}

void processNextMessage() {}

Inbox * initInbox(Outbox * outbox) {
	inbox.outbox = outbox;
	inbox.processNextMessage = &processNextMessage;
	inbox.empty = &_INBOX_empty;

	return &inbox;
}
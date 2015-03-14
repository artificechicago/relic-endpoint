#ifndef __STATUS_CODE_H__
#define __STATUS_CODE_H__

typedef enum _STATUS_CODE {
	OK,
	ERR,
	WAIT
} STATUS_CODE;

void setStatus (STATUS_CODE);

#endif
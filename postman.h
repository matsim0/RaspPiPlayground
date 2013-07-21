#ifndef POSTMAN_H
#define POSTMAN_H

#include "typedefs.h"

void MailboxWrite(uint32_T message, uint32_T channel);
uint32_T MailboxRead(uint32_T channel);

#endif
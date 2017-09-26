#ifndef _SERVER_
#define _SERVER_

#include <czmq.h>

void		publisher_thread(void *args, zctx_t *ctx, void *pipe);
void		responder_thread(void *args, zctx_t *ctx, void *pipe);

#endif /* !_SERVER_ */

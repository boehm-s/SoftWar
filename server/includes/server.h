#ifndef _SERVER_
#define _SERVER_

#include <czmq.h>

void		publisher_thread(void *args, zctx_t *ctx, void *pipe);
void		start_responder(int rep_port);

#endif /* !_SERVER_ */

#include <czmq.h>
#include "includes/util.h"

int		        main() {
    zctx_t *ctx = zctx_new ();
    void *subscriber = zsocket_new (ctx, ZMQ_SUB);
    zsocket_connect (subscriber, "tcp://localhost:%i", 4242);

    zsocket_set_subscribe(subscriber, "");

    while (!zctx_interrupted) {
      char *msg = zstr_recv(subscriber);
      printf("RECIEVED : %s\n", msg);
      free(msg);
    }

    zctx_destroy (&ctx);
  return (0);
}

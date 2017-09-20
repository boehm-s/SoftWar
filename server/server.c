#include "includes/util.h"
#include "includes/server.h"
#include <czmq.h>

void		start_publisher(int pub_port) {
    zctx_t *ctx = zctx_new();
    void *publisher = zsocket_new (ctx, ZMQ_PUB);
    zsocket_bind (publisher, "tcp://*:%i", pub_port);

    while (!zctx_interrupted) {
      /* char msg[1024]; */

      /* if (!fgets(msg, 1024, stdin)) */
      /* 	break; */

      zstr_sendf(publisher, "-- %s", "houhou");
      sleep(1);
    }
    zctx_destroy (&ctx);
}

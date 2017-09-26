#include "includes/util.h"
#include "includes/server.h"
#include <czmq.h>

void	        publisher_thread(void *args, zctx_t *ctx, void *pipe) {
  void *publisher = zsocket_new(ctx, ZMQ_PUB);
  zsocket_bind (publisher, "tcp://*:%i", *((int *)args));
  UNUSED(args);
  UNUSED(pipe);

  printf("PORT NUMBER PUBLISHER : %i\n", *((int *)args));

  while (!zctx_interrupted) {
    /* char msg[1024]; */

    /* if (!fgets(msg, 1024, stdin)) */
    /* 	break; */

    zstr_sendf(publisher, "-- %s", "houhou");
    zclock_sleep(500);
  }
}

void		start_responder(int rep_port) {
  zctx_t        *ctx = zctx_new ();
  void		*responder = zsocket_new(ctx, ZMQ_ROUTER);
  zsocket_bind (responder, "tcp://*:%i", rep_port);

  while (!zctx_interrupted) {
    zmsg_t *msg = zmsg_recv(responder);

    zframe_t *id = zmsg_pop(msg);
    zframe_t *empty = zmsg_pop(msg);
    zframe_t *content = zmsg_pop(msg);
    zmsg_t *response = zmsg_new();

    zmsg_destroy(&msg);
    printf("Content of message is : %s\n", zframe_strdup(content));
    sleep(1);


    zmsg_prepend(response, &id);
    zmsg_append(response, &empty);
    zmsg_append(response, &content);

    zmsg_send(&response, responder);
    zmsg_destroy(&response);

    zframe_destroy(&id);
    zframe_destroy(&empty);
    zframe_destroy(&content);
  }
}

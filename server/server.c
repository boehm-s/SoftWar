#include "includes/init.h"
#include "includes/util.h"
#include "includes/server.h"
#include "includes/game.h"
#include <czmq.h>

void	        publisher_thread(void *args, zctx_t *ctx, void *pipe) {
  void		*publisher = zsocket_new(ctx, ZMQ_PUB);
  t_game_info	*game_info = (t_game_info *) args;

  zsocket_bind (publisher, "tcp://*:%i", ((struct arguments*) game_info->args)->pub_port);
  UNUSED(pipe);


  while (!zctx_interrupted) {
    char *json_game_info;

    cycle_game(game_info);
    json_game_info = game_info_to_JSON(game_info);
    zstr_sendf(publisher, "{\"game_info\": %s}", json_game_info);
    zclock_sleep(game_info->args->cycle_ms);
  }
}

void	        responder_thread(void *args, zctx_t *ctx, void *pipe) {
  void		*responder = zsocket_new(ctx, ZMQ_ROUTER);
  t_game_info	*game_info = (t_game_info *) args;

  zsocket_bind (responder, "tcp://*:%i", ((struct arguments*) game_info->args)->rep_port);
  UNUSED(pipe);

  while (!zctx_interrupted) {
    zframe_t	*response_content;
    zmsg_t	*msg = zmsg_recv(responder);
    zframe_t	*id = zmsg_pop(msg);
    zframe_t	*empty = zmsg_pop(msg);
    zframe_t	*content = zmsg_pop(msg);
    char	*str_content = zframe_strdup(content);
    char	*str_id = zframe_strdup(id);
    zmsg_t	*response = zmsg_new();

    zmsg_destroy(&msg);
    printf("Content of message is : %s\nID is : %s\n", zframe_strdup(content), str_id);

    /* content is used as a response frame */
    response_content = handle_request(game_info, str_id, str_content);

    zmsg_prepend(response, &id);
    zmsg_append(response, &empty);
    zmsg_append(response, &response_content);

    zmsg_send(&response, responder);
    zmsg_destroy(&response);

    zframe_destroy(&id);
    zframe_destroy(&empty);
    zframe_destroy(&content);
  }
}

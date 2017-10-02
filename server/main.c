#include "includes/util.h"
#include "includes/init.h"
#include "includes/server.h"
#include "includes/game.h"

int		        main(int argc, char *argv[]) {

  struct arguments	arguments = init_args(argc, argv);
  t_game_info		*game_info = init_game(&arguments);
  zctx_t		*ctx = zctx_new();
  zlog_category_t	*c;

  if (NULL == (c = init_log())) return -1;

  if (arguments.verbose) {
    zlog_info(c, "\nArguments {\n  rep_port: %i,\n  pub_port: %i,\n  cycle_ms: %i,\n  map_size: %i,\n  log_file: %s,\n  verbose: %i\n}\n", arguments.cycle_ms, arguments.pub_port, arguments.rep_port, arguments.map_size, arguments.log_file, arguments.verbose);
  }

  zlog_fini();

  zthread_fork(ctx, publisher_thread, game_info);
  zthread_fork(ctx, responder_thread, game_info);

  while (2 != game_info->game_status) {
    if (1 == game_info->game_status) {
      UNUSED(game_info);
    }

    printf("Game Status ... %i\n", game_info->game_status);
    zclock_sleep(500);
  }

  puts (" interrupted");
  zctx_destroy (&ctx);
  return (0);
}

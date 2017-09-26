#include "includes/util.h"
#include "includes/init.h"
#include "includes/server.h"
#include "includes/game.h"

int		        main(int argc, char *argv[]) {

  struct arguments	arguments = init_args(argc, argv);
  t_game_info		*game_info = init_game(&arguments);
  zctx_t		*ctx = zctx_new ();
  zlog_category_t	*c;
  int			state = 0;

  if (NULL == (c = init_log())) return -1;

  if (arguments.verbose) {
    zlog_info(c, "\nArguments {\n  rep_port: %i,\n  pub_port: %i,\n  cycle_ms: %i,\n  map_size: %i,\n  log_file: %s,\n  verbose: %i\n}\n", arguments.cycle_ms, arguments.pub_port, arguments.rep_port, arguments.map_size, arguments.log_file, arguments.verbose);
  }

  zlog_fini();

  zthread_fork(ctx, publisher_thread, &arguments.pub_port);
  zthread_fork(ctx, responder_thread, &arguments.rep_port);



  while (2 != state) {
    if (1 == state) {

    }

    zclock_sleep(arguments.cycle_ms);
  }

  puts (" interrupted");
  zctx_destroy (&ctx);

  return (0);
}

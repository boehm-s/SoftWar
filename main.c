#include "includes/util.h"
#include "includes/parse_arg.h"
#include "zlog.h"


// TODO : zlog_category_t	*init_log()
// TODO : struct arguments	*init_args()

int		        main(int argc, char *argv[]) {

  int			rc;
  zlog_category_t	*c;
  struct arguments	arguments;
  struct argp		argp = get_argp();

  rc = zlog_init("./zlog.conf");
  if (rc) {
    printf("init failed\n");
    return -1;
  }

  c = zlog_get_category("softwar");


  if (!c) {
    printf("get cat fail\n");
    zlog_fini();
    return -2;
  }

  zlog_info(c, "hello, zlog");
  zlog_fini();

  /* default values */
  arguments.rep_port = 4242;
  arguments.pub_port = 4243;
  arguments.cycle_ms = 500000;
  arguments.map_size = 5;
  arguments.log_file = NULL;
  arguments.verbose = 0;

  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  if (arguments.verbose){}

  printf("\nArguments {\n  rep_port: %i,\n  pub_port: %i,\n  cycle_ms: %i,\n  map_size: %i,\n  log_file: %s,\n  verbose: %i\n}\n", arguments.cycle_ms, arguments.pub_port, arguments.rep_port, arguments.map_size, arguments.log_file, arguments.verbose);

  return (0);
}

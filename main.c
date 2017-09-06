#include "includes/util.h"
#include "includes/init.h"


/* TODO : zlog_category_t	*init_log() */

int		        main(int argc, char *argv[]) {

  struct arguments	arguments = init_args(argc, argv);
  zlog_category_t	*c;

  if (NULL == (c = init_log()))
    return -1;

  zlog_info(c, "hello, zlog");
  zlog_fini();


  if (arguments.verbose) {
    printf("\nArguments {\n  rep_port: %i,\n  pub_port: %i,\n  cycle_ms: %i,\n  map_size: %i,\n  log_file: %s,\n  verbose: %i\n}\n", arguments.cycle_ms, arguments.pub_port, arguments.rep_port, arguments.map_size, arguments.log_file, arguments.verbose);
  }

  return (0);
}

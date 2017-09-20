#include "includes/util.h"
#include "includes/init.h"
#include "includes/server.h"

int		        main(int argc, char *argv[]) {

  /* get arguments in struct */
  struct arguments	arguments = init_args(argc, argv);

  /* init logger with conf file*/
  zlog_category_t	*c;
  if (NULL == (c = init_log()))
    return -1;

  if (arguments.verbose) {
    zlog_info(c, "\nArguments {\n  rep_port: %i,\n  pub_port: %i,\n  cycle_ms: %i,\n  map_size: %i,\n  log_file: %s,\n  verbose: %i\n}\n", arguments.cycle_ms, arguments.pub_port, arguments.rep_port, arguments.map_size, arguments.log_file, arguments.verbose);
  }

  zlog_fini();

  /* here goes the server ! */
  start_publisher(arguments.pub_port);

  return (0);
}

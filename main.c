#include "includes/util.h"
#include "includes/parse_arg.h"
#include "zlog.h"


int		        main(int argc, char *argv[]) {

  int			rc;
  zlog_category_t	*c;
  struct arguments	arguments;
  FILE			*outstream;
  struct argp		argp = get_argp();

  rc = zlog_init("./zlog.conf");
  if (rc) {
    printf("init failed\n");
    return -1;
  }

  c = zlog_get_category("my_cat");
  if (!c) {
    printf("get cat fail\n");
    zlog_fini();
    return -2;
  }

  zlog_info(c, "hello, zlog");
  zlog_fini();



  arguments.rep_port = 4242;
  arguments.pub_port = 4243;
  arguments.cycle_ms = 500000;
  arguments.map_size = 5;
  arguments.log_file = NULL;
  arguments.verbose = 0;

  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  outstream = arguments.log_file
    ? fopen (arguments.log_file, "w")
    : stdout;

  if (arguments.verbose)
    fprintf (outstream, "%s\n", "coucou test\nHaha ha hahaha hahahahahahah\nNon, ce n'est pas moi !");

  printf("\nArguments {\n  rep_port: %i,\n  pub_port: %i,\n  cycle_ms: %i,\n  map_size: %i,\n  log_file: %s,\n  verbose: %i\n}\n", arguments.cycle_ms, arguments.pub_port, arguments.rep_port, arguments.map_size, arguments.log_file, arguments.verbose);

  return (0);
}

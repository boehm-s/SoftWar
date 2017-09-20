#ifndef _INIT_
#define _INIT_

#include <argp.h>
#include "zlog.h"

struct	arguments {
  char	**args;
  int	verbose;
  int	rep_port;
  int	pub_port;
  int	cycle_ms;
  int	map_size;
  char	*log_file;
};

struct argp		get_argp();
struct arguments	init_args(int argc, char *argv[]);
zlog_category_t		*init_log();

#endif /* !_INIT_ */

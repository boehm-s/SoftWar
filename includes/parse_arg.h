#ifndef _PARSE_ARG_
#define _PARSE_ARG_

#include <argp.h>

struct	arguments {
  char	**args;
  int	verbose;
  int	rep_port;
  int	pub_port;
  int	cycle_ms;
  int	map_size;
  char	*log_file;
};

struct argp	get_argp();

#endif /* !_PARSE_ARG_ */

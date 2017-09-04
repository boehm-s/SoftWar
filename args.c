#include "includes/util.h"
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

static error_t parse_opt (int key, char *arg, struct argp_state *state) {
  struct arguments *arguments = state->input;

  switch (key) {
    case 'r': arguments->rep_port = atoi(arg);	         break;
    case 'p': arguments->pub_port = atoi(arg);	         break;
    case 'c': arguments->cycle_ms = atoi(arg);	         break;
    case 'v': arguments->verbose = 1;		         break;
    case 'l': arguments->log_file = arg;	         break;
    case 's': arguments->map_size = atoi(arg);	         break;

    case ARGP_KEY_ARG:		return (state->arg_num != 0) ? ARGP_KEY_ERROR : ARGP_ERR_UNKNOWN; break;
    case ARGP_KEY_SUCCESS:	break;
    case ARGP_KEY_ERROR:        argp_usage (state); break;

    case ARGP_KEY_ARGS:
      arguments->args = &state->argv[state->next];
      state->next = state->argc;
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp_option options[] = {
  {"rep-port",	'r', "rep_port",	OPTION_ARG_OPTIONAL, "port that recieve the commands of the clients and fulfill the request",	0},
  {"pub-port",	'p', "pub_port",	OPTION_ARG_OPTIONAL, "port used to send notifications to the clients",				1},
  {"cycle",	'c', "cycle_ms",	OPTION_ARG_OPTIONAL, "number of microseconds (ms) of a cycle lifetime",				2},
  {"verbose",	'v', 0,			OPTION_ARG_OPTIONAL, "Produce verbose output",							3},
  {"log",	'l', 0,			OPTION_ARG_OPTIONAL, "Specify a log file",							4},
  {"size",	's', "map_size",	OPTION_ARG_OPTIONAL, "Specify the size of the map",						5},
  {0}
};


struct argp		get_argp() {
  static char args_doc[] = "";
  static char doc[] = "SoftWar - Usage : ./SoftWar -v --size=8 --log=/tmp/soft_war.log --cycle=1000000 --rep-port=4242 --pub-port=4243";
  static struct argp_child children[] = {{0}};
  static struct argp argp = {options, parse_opt, args_doc, doc, children, 0, 0};

  return argp;
}

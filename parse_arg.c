#include <argp.h>

#include "includes/util.h"
#include "includes/parse_arg.h"


static struct argp_option options[] = {
  {"rep-port",	'r', "4242",	0, "port that recieve the commands of the clients and fulfill the request",	0},
  {"pub-port",	'p', "4243",	0, "port used to send notifications to the clients",				0},
  {"cycle",	'c', "500000",	0, "number of microseconds (ms) of a cycle lifetime",				0},
  {"verbose",	'v', 0,		0, "Produce verbose output",							0},
  {"log",	'l', 0,		0, "Specify a log file",							0},
  {"size",	's', "5",	0, "Specify the size of the map",						0},
  {0}
};

static error_t parse_opt (int key, char *arg, struct argp_state *state) {
  struct arguments *arguments = state->input;

  switch (key) {
    case 'r': arguments->rep_port = atoi(arg);		break;
    case 'p': arguments->pub_port = atoi(arg);		break;
    case 'c': arguments->cycle_ms = atoi(arg);		break;
    case 'v': arguments->verbose = 1;			break;
    case 'l': arguments->log_file = arg;		break;
    case 's': arguments->map_size = atoi(arg);		break;
    case ARGP_KEY_ARG:
      if (state->arg_num >= 2)
	argp_usage(state);
      arguments->args[state->arg_num] = arg;
      break;
    case ARGP_KEY_END:
      if (state->arg_num < 2)
	argp_usage (state);
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static char args_doc[] = "test args_doc ";
static char doc[] = "SoftWar - Usage : ./SoftWar -v --size 8 --log /tmp/soft_war.log --cycle 1000000 --rep-port 4242 --pub-port 4243";
static struct argp_child children[] = {{0}};
static struct argp argp = {options, parse_opt, args_doc, doc, children, 0, 0};

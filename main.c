#include "includes/util.h"
#include "includes/parse_arg.h"
#include "zlog.h"



static struct argp_option options[] = {
  {"rep-port",	'r', "rep_port",	OPTION_ARG_OPTIONAL, "port that recieve the commands of the clients and fulfill the request",	0},
  {"pub-port",	'p', "pub_port",	OPTION_ARG_OPTIONAL, "port used to send notifications to the clients",				1},
  {"cycle",	'c', "cycle_ms",	OPTION_ARG_OPTIONAL, "number of microseconds (ms) of a cycle lifetime",				2},
  {"verbose",	'v', 0,			OPTION_ARG_OPTIONAL, "Produce verbose output",							3},
  {"log",	'l', 0,			OPTION_ARG_OPTIONAL, "Specify a log file",							4},
  {"size",	's', "map_size",	OPTION_ARG_OPTIONAL, "Specify the size of the map",						5},
  {0}
};

static error_t parse_opt (int key, char *arg, struct argp_state *state) {
  struct arguments *arguments = state->input;

  switch (key) {
  case 'r': arguments->rep_port = atoi(arg);	        printf("1\n");  break;
  case 'p': arguments->pub_port = atoi(arg);		printf("2\n");  break;
  case 'c': arguments->cycle_ms = atoi(arg);		printf("3\n");  break;
  case 'v': arguments->verbose = 1;			printf("4\n");  break;
  case 'l': arguments->log_file = arg;			printf("5\n");  break;
  case 's': arguments->map_size = atoi(arg);		printf("6\n");  break;

  case ARGP_KEY_ARG:		return (state->arg_num != 0) ? ARGP_KEY_ERROR : ARGP_ERR_UNKNOWN; break;
  case ARGP_KEY_SUCCESS:	break;
  case ARGP_KEY_ERROR:		argp_usage (state); break;
  case ARGP_KEY_ARGS:
    arguments->args = &state->argv[state->next];
    state->next = state->argc;
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static char args_doc[] = "";
static char doc[] = "SoftWar - Usage : ./SoftWar -v --size 8 --log /tmp/soft_war.log --cycle 1000000 --rep-port 4242 --pub-port 4243";
static struct argp_child children[] = {{0}};
static struct argp argp = {options, parse_opt, args_doc, doc, children, 0, 0};


int		main(int argc, char *argv[]) {

  int rc;
  zlog_category_t *c;

  struct arguments arguments;
  FILE *outstream;

  char waters[] = " a place to stay enough to eat somewhere old heroes shuffle safely down the street where you can speak out loud about your doubts and fears and what's more no-one ever disappears you never hear their standard issue kicking in your door you can relax on both sides of the tracks and maniacs don't blow holes in bandsmen by remote control and everyone has recourse to the law and no-one kills the children anymore and no-one kills the children anymore  --\"the gunners dream\", Roger Waters, 1983\n";

  UNUSED(argc);
  UNUSED(argv);
  UNUSED(arguments);
  UNUSED(outstream);
  UNUSED(waters);
  UNUSED(argp);

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

  if (arguments.log_file)
    outstream = fopen (arguments.log_file, "w");
  else
    outstream = stdout;

  fprintf (outstream, "rep_port = %i\npub_port = %i\n\n",
  	   arguments.rep_port, arguments.pub_port);

  if (arguments.verbose)
    fprintf (outstream, "%s\n", waters);

  return (0);
}

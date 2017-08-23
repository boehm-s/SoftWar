#include "includes/util.h"
#include "includes/parse_arg.h"
/* #include "includes/parse_arg.h" */
#include "zlog.h"



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


int		main(int argc, char *argv[]) {

  int rc;
  zlog_category_t *c;

  struct arguments arguments;
  FILE *outstream;

  char waters[] = " a place to stay enough to eat somewhere old heroes shuffle safely down the street where you can speak out loud about your doubts and fears and what's more no-one ever disappears you never hear their standard issue kicking in your door you can relax on both sides of the tracks and maniacs don't blow holes in bandsmen by remote control and everyone has recourse to the law and no-one kills the children anymore and no-one kills the children anymore  --\"the gunners dream\", Roger Waters, 1983\n";

  UNUSED(argc);
  UNUSED(argv);

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

  /* Set argument defaults */
  arguments.rep_port = 4242;
  arguments.pub_port = 4243;
  arguments.cycle_ms = 500000;
  arguments.map_size = 5;
  arguments.log_file = NULL;
  arguments.verbose = 0;

  /* Where the magic happens */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  /* Where do we send output? */
  if (arguments.log_file)
    outstream = fopen (arguments.log_file, "w");
  else
    outstream = stdout;

  /* Print argument values */
  fprintf (outstream, "rep_port = %i\npub_port = %i\n\n",
	   arguments.rep_port, arguments.pub_port);
  fprintf (outstream, "ARG1 = %s\nARG2 = %s\n\n",
	   arguments.args[0],
	   arguments.args[1]);

  /* If in verbose mode, print song stanza */
  if (arguments.verbose)
    fprintf (outstream, "%s\n", waters);


  return (0);
}

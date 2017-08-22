struct	arguments {
  char	**args;
  int	verbose;
  int	rep_port;
  int	pub_port;
  int	cycle_ms;
  int	map_size;
  char	*log_file;
};

static error_t parse_opt (int key, char *arg, struct argp_state *state);

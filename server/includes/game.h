#ifndef _GAME_
#define _GAME_

#include <collectc/array.h>

enum notif_type {
  cycle_info,
  game_started,
  game_finished,
  client_dead,
  client_win
};

typedef struct s_notif {
  enum notif_type	notification_type;
  void			*data;
} t_notif;

typedef struct s_game_info {
  unsigned int	map_size;
  unsigned int	game_status;
  Array		*players;
  Array		*map;
} t_game_info;

typedef struct s_player {
  char		*name;
  unsigned int	x;
  unsigned int	y;
  unsigned int	energy;
  unsigned int	looking;
} t_player;

typedef struct s_enegry_cell {
  unsigned int	x;
  unsigned int	y;
  unsigned int	value;
} t_energy_cell;

t_game_info	*init_game(struct arguments *arguments);

#endif /* !_GAME_ */

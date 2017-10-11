#ifndef _GAME_
#define _GAME_

#include <collectc/array.h>
#include <czmq.h>

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
  unsigned int		map_size;
  unsigned int		game_status;
  Array			*players;
  Array			*map;
  struct arguments	*args;
} t_game_info;

typedef struct	s_player {
  char		*name;
  unsigned int	x;
  unsigned int	y;
  unsigned int	energy;
  unsigned int	looking;
} t_player;

typedef struct	s_enegry_cell {
  unsigned int	x;
  unsigned int	y;
  unsigned int	value;
} t_energy_cell;

typedef struct	s_command {
  char		*cmd;
  int		(*fn)(t_game_info *game_info, char *id, char *args);
} t_command;

t_game_info	*init_game(struct arguments *arguments);
zframe_t        *handle_request(t_game_info *game_info, char *id, char *content);
int		cmp_players_name(const void *el, const void *player2);

char		*players_to_JSON(Array *players);
char		*map_to_JSON(Array *map);
char		*game_info_to_JSON(t_game_info *game_info);


int		identity(t_game_info *game_info, char *id, char *args);
int		forward(t_game_info *game_info, char *id, char *args);
int		backward(t_game_info *game_info, char *id, char *args);
int		leftwd(t_game_info *game_info, char *id, char *args);
int		rightwd(t_game_info *game_info, char *id, char *args);
int	        left(t_game_info *game_info, char *id, char *args);
int	        right(t_game_info *game_info, char *id, char *args);
int	        looking(t_game_info *game_info, char *id, char *args);
int	        gather(t_game_info *game_info, char *id, char *args);
int	        watch(t_game_info *game_info, char *id, char *args);
int	        attack(t_game_info *game_info, char *id, char *args);
int	        selfid(t_game_info *game_info, char *id, char *args);
int	        selfstats(t_game_info *game_info, char *id, char *args);
int	        inspect(t_game_info *game_info, char *id, char *args);
int	        next(t_game_info *game_info, char *id, char *args);
int	        jump(t_game_info *game_info, char *id, char *args);


#endif /* !_GAME_ */

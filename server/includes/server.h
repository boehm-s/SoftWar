#ifndef _SERVER_
#define _SERVER_

#include <czmq.h>
#include <collectc/array.h>

typedef struct s_game_info {
unsigned int	map_size;
unsigned int	game_status;
Array		*players;
Array		*energy_cells;
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

void		publisher_thread(void *args, zctx_t *ctx, void *pipe);
void		responder_thread(void *args, zctx_t *ctx, void *pipe);

#endif /* !_SERVER_ */

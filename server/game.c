#include "includes/game.h"
#include "includes/init.h"

t_game_info	*init_game(struct arguments *arguments) {
  t_game_info	game_info;
  int		i;

  game_info.map_size = arguments->map_size;
  game_info.game_status = 0;

  if (CC_OK != array_new(&game_info.players)
      || CC_OK != array_new(&game_info.energy_cells))
    return NULL;

  for (i = 0; i < (game_info.map_size * game_info.map_size); i++) {

  }

  /* JS */
  /* for (i = 0; i < 8*8; i++) */
  /* console.log(`${(Math.floor(i/8) % 8) + 1} - ${(i % 8) + 1}`); */

}

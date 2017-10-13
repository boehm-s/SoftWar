#include "includes/init.h"
#include "includes/util.h"
#include "includes/game.h"
#include "includes/server.h"

static t_command	commands_tab[] = {
  {"identity",	&identity},
  {"forward",	&forward},
  {"backward",	&backward},
  {"leftfwd",	&leftfwd},
  {"rightfwd",	&rightfwd},
  {"left",	&left},
  {"right",	&right},
  {"looking",	&looking},
  {"gather",	&gather},
  {"watch",	&watch},
  {"attack",	&attack},
  {"selfid",	&selfid},
  {"selfstats", &selfstats},
  {"inspect",	&inspect},
  {"next",	&next},
  {"jump",	&jump},
  {NULL, NULL}
};

t_game_info	*init_game(struct arguments *arguments) {
  t_game_info	*game_info = malloc(sizeof(t_game_info));
  int		i;


  game_info->args = arguments;
  game_info->map_size = arguments->map_size;
  game_info->game_status = 0;

  if (CC_OK != array_new(&game_info->players)
      || CC_OK != array_new(&game_info->map))
    return NULL;

  for (i = 0; i < (int) (game_info->map_size * game_info->map_size); i++) {
    t_energy_cell *cell = malloc(sizeof(t_energy_cell *));
    enum cc_stat status;

    cell->x = ((i/game_info->map_size) % game_info->map_size);
    cell->y = (i % game_info->map_size);
    cell->value = 0;

    status = array_add(game_info->map, cell);

    if (CC_OK != status)
      return NULL;
  }

  return (game_info);
}


zframe_t		*handle_request(t_game_info *game_info, char *id, char *content) {
  zframe_t      *res_frame;
  char		*cmd = strtok(content, "|");
  char		*cmd_args = strtok(NULL, "|");
  int		i = 0;

  UNUSED(res_frame);
  UNUSED(cmd_args);
  while (NULL != commands_tab[i].cmd) {
    if (strcmp(cmd, commands_tab[i].cmd) == 0) {
      commands_tab[i].fn(game_info, id, cmd_args);
      printf("ID: %s\nCOMMAND : %s\n", id, cmd);
    }
    i++;
  }

  res_frame = zframe_new("OK", 2);
  return res_frame;
}


void		cycle_game(t_game_info *game_info) {
  overflow_cell(game_info);
  players_cycle(game_info);
}

void		overflow_cell(t_game_info *game_info) {
  int		i;
  unsigned int	x = rand() % game_info->map_size;
  unsigned int	y = rand() % game_info->map_size;
  int		val = (rand() % (15 + 1 - 5)) + 5;
  size_t        map_length = array_size(game_info->map);

  for (i = 0; i < (int) map_length; i++) {
    t_energy_cell	*cell;

    array_get_at(game_info->map, i, (void *)&cell);
    if (cell ->x == x && cell->y == y && (cell->value + val) <= 100)
      cell->value += val;
  }
}

void		players_cycle(t_game_info *game_info) {
  int		i;
  size_t        players_length = array_size(game_info->players);

  for (i = 0; i < (int) players_length; i++) {
    t_player	*player;

    array_get_at(game_info->players, i, (void *)&player);
    player->energy -= 2;
    if (player->energy > 100 || player->energy <= 0)
      player->looking = 5;
  }
}

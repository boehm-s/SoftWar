#include "includes/init.h"
#include "includes/util.h"
#include "includes/game.h"
#include "includes/server.h"

static t_command	commands_tab[] = {
  {"identity",	&identity},
  {"forward",	&forward},
  {"backward",	&backward},
  {"leftwd",	&leftwd},
  {"rightwd",	&rightwd},
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

#include "includes/init.h"
#include "includes/util.h"
#include "includes/game.h"

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
    t_energy_cell cell;
    enum cc_stat status;

    cell.x = ((i/game_info->map_size) % game_info->map_size);
    cell.y = (i % game_info->map_size);
    cell.value = 0;

    status = array_add(game_info->map, &cell);

    if (CC_OK != status)

      return NULL;
  }

  return (game_info);
}


void		handle_request(t_game_info *game_info, char *id, char *content, zframe_t *res_frame) {
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
  }
}

char		*game_info_to_JSON(t_game_info *game_info) {
  /* char		*buf; */
  /* size_t        sz; */
  int		i;
  size_t        player_length = array_size(game_info->players);

  for (i = 0; i < (int) player_length; i++) {
    int sz = 5 + 11;
    char *str = malloc(sizeof(char) * sz);
    t_player *player;
    array_get_at(game_info->players, i, (void *)&player);
    snprintf(str, sz + 1, "{\"name\":\"%s\"}", player->name);

    /* int str_size =  (5+10+10+3+1) + 52; */
    /* char *json_str = malloc(sizeof(char) * str_size); */
    /* snprintf(json_str, str_size + 1, "{\"name\": \"%s\",\"x\":\"%i\",\"y\":\"%i\",\"energy\":\"%i\",\"looking\":\"%i\"}", game_info->players->buffer[i]->name, game_info->players->buffer[i]->x, game_info->players->buffer[i]->y, game_info->players->buffer[i]->energy, game_info->players->buffer[i]->looking); */
    /* printf("JSON : %s\n", json_str); */
  }
  return "coucou";
}

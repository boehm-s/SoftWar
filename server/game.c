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
    i++;
  }
}

char		*game_info_to_JSON(t_game_info *game_info) {
  char		*buf = malloc(1);
  char		**infos;
  int		i;
  size_t        player_length = array_size(game_info->players);

  infos = malloc(sizeof(char *) * (player_length + 1));
  *buf = '\0';
  for (i = 0; i < (int) player_length; i++) {
    t_player	*player;
    char	*str;

    array_get_at(game_info->players, i, (void *)&player);
    str = malloc(sizeof(char) * (50 + 5 + 10 + 10 + 3 + 1 + 1));
    sprintf(str, "{\"name\":\"%s\",\"x\":\"%i\",\"y\":\"%i\",\"energy\":\"%i\",\"looking\":\"%i\"}", player->name, player->x, player->x, player->energy, player->looking);
    infos[i] = str;
  }

  for (i = 0; i < (int) player_length; i++) {
    int		new_size;
    char	*tmp;

    new_size = strlen(infos[i]) + strlen(buf) + 3;
    tmp = realloc(buf, new_size);
    if (!tmp) return "{}";
    buf = tmp;

    if (0 == i && 1 != (int) player_length)
      sprintf(buf, "[%s,", infos[i]);
    else if (i == ((int) player_length - 1) && 0 != i)
      sprintf(buf, "%s%s]", buf, infos[i]);
    else if (1 != (int) player_length)
      sprintf(buf, "%s%s,", buf, infos[i]);
    else
      sprintf(buf, "[%s]", infos[i]);
  }
  return buf;
}

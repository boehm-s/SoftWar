#include "includes/init.h"
#include "includes/util.h"
#include "includes/game.h"

char		*players_to_JSON(Array *players) {
  char		*buf = malloc(1);
  char		**infos;
  int		i;
  size_t        player_length = array_size(players);

  if (0 == player_length) return "[]";

  infos = malloc(sizeof(char *) * (player_length + 1));
  *buf = '\0';
  for (i = 0; i < (int) player_length; i++) {
    t_player	*player;
    char	*str;

    array_get_at(players, i, (void *)&player);
    str = malloc(sizeof(char) * (50 + 5 + 10 + 10 + 3 + 1 + 1));
    sprintf(str, "{\"name\":\"%s\",\"x\":\"%i\",\"y\":\"%i\",\"energy\":\"%i\",\"looking\":\"%i\"}", player->name, player->x, player->y, player->energy, player->looking);
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

char		*map_to_JSON(Array *map) {
  char		*buf = malloc(1);
  char		**infos;
  int		i;
  size_t        map_length = array_size(map);

  infos = malloc(sizeof(char *) * (map_length + 1));
  for (i = 0; i < (int) map_length; i++) {
    t_energy_cell	*cell;
    char		*str;

    array_get_at(map, i, (void *)&cell);
    str = malloc(sizeof(char) * (27 + 10 + 10 + 3 + 2));
    sprintf(str, "{\"x\":\"%i\",\"y\":\"%i\",\"value\":\"%i\"}", cell->x, cell->y, cell->value);
    infos[i] = str;
  }

  for (i = 0; i < (int) map_length; i++) {
    int		new_size;
    char	*tmp;

    new_size = strlen(infos[i]) + strlen(buf) + 3;
    tmp = realloc(buf, new_size);
    if (!tmp) return "{}";
    buf = tmp;

    if (0 == i && 1 != (int) map_length)
      sprintf(buf, "[%s,", infos[i]);
    else if (i == ((int) map_length - 1) && 0 != i)
      sprintf(buf, "%s%s]", buf, infos[i]);
    else if (1 != (int) map_length)
      sprintf(buf, "%s%s,", buf, infos[i]);
    else
      sprintf(buf, "[%s]", infos[i]);
  }
  return buf;
}

/* PB WITH THE MAP */
char		*game_info_to_JSON(t_game_info *game_info) {
  char		*json_players = players_to_JSON(game_info->players);
  char		*json_map = map_to_JSON(game_info->map);
  int		json_game_size = strlen(json_players) + strlen(json_map) + 65;
  char		*json_game = malloc(sizeof(char) * json_game_size);

  sprintf(json_game, "{\"map_size\":\"%i\",\"game_status\":\"%i\",\"players\":%s,\"map\":%s}", game_info->map_size, game_info->game_status, json_players, json_map);

  return json_game;
}

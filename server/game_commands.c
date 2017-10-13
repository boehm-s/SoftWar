#include "includes/util.h"
#include "includes/game.h"

int		cmp_players_name(const void *el, const void *player2) {
  int		i;

  i = strcmp((char *) el, ((t_player *) player2)->name);
  return i;
}

int		identity(t_game_info *game_info, char *id, char *args) {
  t_player	*player = malloc(sizeof(t_player));
  size_t	player_length;
  enum cc_stat	status;

  UNUSED(args);
  player_length = array_size(game_info->players);

  if (0 != array_contains_value(game_info->players, id, &cmp_players_name)
      || 4 <= player_length)
    return 1;

  player->name = id;
  player->energy = 50;
  player->looking = 0;

  if (0 == player_length % 2) {
    player->x = 0;
    player->y = player_length < 2 ? 0 : (game_info->map_size - 1);
  } else {
    player->x = (game_info->map_size - 1);
    player->y = player_length < 2 ? 0 : (game_info->map_size - 1);
  }

  status = array_add(game_info->players, player);

  if (3 == player_length && status == CC_OK)
    game_info->game_status = 1;

  return status == CC_OK ? 0 : 1;
}

int		forward(t_game_info *game_info, char *id, char *args) {
  int		i;
  size_t        players_length = array_size(game_info->players);

  for (i = 0; i < (int) players_length; i++) {
    t_player	*player;
    array_get_at(game_info->players, i, (void *)&player);

    if (0 == strcmp(player->name, id) && 0 != player->x)
      player->x--;

  }

  UNUSED(args);
  return 0;
}

int		backward(t_game_info *game_info, char *id, char *args) {
  int		i;
  size_t        players_length = array_size(game_info->players);

  for (i = 0; i < (int) players_length; i++) {
    t_player	*player;
    array_get_at(game_info->players, i, (void *)&player);

    if (0 == strcmp(player->name, id) && player->x != game_info->map_size - 1)
      player->x++;
  }
  UNUSED(args);
  return 0;
}

int		leftfwd(t_game_info *game_info, char *id, char *args) {
  int		i;
  size_t        players_length = array_size(game_info->players);

  for (i = 0; i < (int) players_length; i++) {
    t_player	*player;
    array_get_at(game_info->players, i, (void *)&player);

    if (0 == strcmp(player->name, id) && 0 != player->y)
	player->y--;
  }
  UNUSED(args);
  return 0;
}

int		rightfwd(t_game_info *game_info, char *id, char *args) {
  int		i;
  size_t        players_length = array_size(game_info->players);

  for (i = 0; i < (int) players_length; i++) {
    t_player	*player;
    array_get_at(game_info->players, i, (void *)&player);

    if (0 == strcmp(player->name, id) && player->y != game_info->map_size - 1)
      player->y++;
  }
  UNUSED(args);
  return 0;
}

int	        left(t_game_info *game_info, char *id, char *args) {
  UNUSED(game_info);
  UNUSED(id);
  UNUSED(args);
  return 0;
}

int	        right(t_game_info *game_info, char *id, char *args) {
  UNUSED(game_info);
  UNUSED(id);
  UNUSED(args);
  return 0;
}

int	        looking(t_game_info *game_info, char *id, char *args) {
  UNUSED(game_info);
  UNUSED(id);
  UNUSED(args);
  return 0;
}

int	        gather(t_game_info *game_info, char *id, char *args) {
  int		i;
  t_player	*player;
  t_energy_cell	*cell;
  size_t        players_length = array_size(game_info->players);
  size_t        map_length = array_size(game_info->map);

  for (i = 0; i < (int) players_length; i++) {
    array_get_at(game_info->players, i, (void *)&player);

    if (0 == strcmp(player->name, id))
      break;
  } /* I've got my player */


  for (i = 0; i < (int) map_length; i++) {
    array_get_at(game_info->map, i, (void *)&cell);
    if (cell->x == player->x && cell->y == player->y)
      break;
  } /* I've got my cell */


  printf("player : %s - (%i:%i)\n", player->name, player->x, player->y);
  printf("cell : %i -- (%i:%i)\n", cell->value, cell->x, cell->y);

  player->energy += cell->value;
  cell->value = 0;

  UNUSED(args);
  return 0;
}

int	        watch(t_game_info *game_info, char *id, char *args) {
  UNUSED(game_info);
  UNUSED(id);
  UNUSED(args);
  return 0;
}

int	        attack(t_game_info *game_info, char *id, char *args) {
  UNUSED(game_info);
  UNUSED(id);
  UNUSED(args);
  return 0;
}

int	        selfid(t_game_info *game_info, char *id, char *args) {
  UNUSED(game_info);
  UNUSED(id);
  UNUSED(args);
  return 0;
}

int	        selfstats(t_game_info *game_info, char *id, char *args) {
  UNUSED(game_info);
  UNUSED(id);
  UNUSED(args);
  return 0;
}

int	        inspect(t_game_info *game_info, char *id, char *args) {
  UNUSED(game_info);
  UNUSED(id);
  UNUSED(args);
  return 0;
}

int	        next(t_game_info *game_info, char *id, char *args) {
  UNUSED(game_info);
  UNUSED(id);
  UNUSED(args);
  return 0;
}

int	        jump(t_game_info *game_info, char *id, char *args) {
  UNUSED(game_info);
  UNUSED(id);
  UNUSED(args);
  return 0;
}

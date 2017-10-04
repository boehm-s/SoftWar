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

  UNUSED(args);
  if (0 != array_contains_value(game_info->players, id, &cmp_players_name))
    return 1;

  player->name = id;
  player->energy = 50;
  player->looking = 0;

  player_length = array_size(game_info->players);
  if (0 == player_length % 2) {
    player->x = 0;
    player->y = player_length < 2 ? 0 : game_info->map_size;
  } else {
    player->x = player_length < 2 ? 0 : game_info->map_size;
    player->y = 0;
  }
  return 0;
}

int		forward(t_game_info *game_info, char *id, char *args) {
  UNUSED(game_info);
  UNUSED(id);
  UNUSED(args);
  return 0;
}

int		backward(t_game_info *game_info, char *id, char *args) {
  UNUSED(game_info);
  UNUSED(id);
  UNUSED(args);
  return 0;
}

int		leftwd(t_game_info *game_info, char *id, char *args) {
  UNUSED(game_info);
  UNUSED(id);
  UNUSED(args);
  return 0;
}

int		rightwd(t_game_info *game_info, char *id, char *args) {
  UNUSED(game_info);
  UNUSED(id);
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
  UNUSED(game_info);
  UNUSED(id);
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

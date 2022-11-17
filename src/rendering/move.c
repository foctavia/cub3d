/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:52:35 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/17 11:37:11 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(t_game *game, float dest_x, float dest_y)
{
	float	square_x;
	float	square_y;

	square_y = dest_y * game->map->height / game->mlx->height;
	square_x = dest_x * game->map->width / game->mlx->width;
	if (game->map->content[(int)square_y][(int)square_x] == WALL)
		return (TRUE);
	return (FALSE);
}

static void	get_dest_coord(t_player *player, int key, t_coord *dest)
{
	dest->x = player->pos.x;
	dest->y = player->pos.y;
	if ((player->dir == RIGHT && key == UP) \
		|| (player->dir == LEFT && key == DOWN))
		dest->x += 5;
	else if ((player->dir == LEFT && key == UP) \
		|| (player->dir == RIGHT && key == DOWN))
		dest->x -= 5;
	else if ((player->dir == DOWN && key == UP) \
		|| (player->dir == UP && key == DOWN))
		dest->y += 5;
	else if ((player->dir == UP && key == UP) \
		|| (player->dir == DOWN && key == DOWN))
		dest->y -= 5;
}

int	change_player_pos(t_game *game, t_player *player, int key)
{
	t_coord	*dest;

	dest = malloc(sizeof(t_coord));
	if (!dest)
		ft_error(ERR_MALLOC, 0, NULL, game);
	ft_memset(dest, 0, sizeof(t_coord));
	get_dest_coord(player, key, dest);
	if (is_wall(game, dest->x, dest->y))
	{
		free(dest);
		return (EXIT_FAILURE);
	}
	draw_player(game, game->mlx->minimap, player->pos, HEX_BLACK);
	player->pos.x = dest->x;
	player->pos.y = dest->y;
	free(dest);
	return (EXIT_SUCCESS);
}

int	move_player(t_game *game, t_player *player, int key)
{
	change_player_pos(game, player, key);
	ft_render(game);
	return (EXIT_SUCCESS);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_RIGHT || keycode == KEY_D)
		change_player_dir(game->player, keycode);
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		change_player_dir(game->player, keycode);
	else if (keycode == KEY_UP || keycode == KEY_W)
		return (move_player(game, game->player, UP));
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		return (move_player(game, game->player, DOWN));
	else if (keycode == KEY_ESC)
		return (close_window(game));
	return (EXIT_SUCCESS);
}

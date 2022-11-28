/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:52:35 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/28 19:23:00 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *game, float dest_x, float dest_y)
{
	float	square_x;
	float	square_y;

	square_y = dest_y / game->mlx->minimap->elem_size;
	square_x = dest_x / game->mlx->minimap->elem_size;
	if ((int)square_y < 0 || (int)square_x < 0 || \
		(int)square_y >= game->map->height || (int)square_x >= game->map->width)
		return (FALSE);
	if (game->map->content[(int)square_y][(int)square_x] == WALL)
		return (TRUE);
	return (FALSE);
}

void	move_up(t_game *game, t_player *player)
{
	if (!is_wall(game, player->pos.y + player->dir.y, player->pos.x + player->dir.x))
	{
		player->pos.y += player->dir.y;
		player->pos.x += player->dir.x;
		player->square.y = player->pos.y / game->mlx->minimap->elem_size;
		player->square.x = player->pos.x / game->mlx->minimap->elem_size;
	}
}

void	move_down(t_game *game, t_player *player)
{
	if (!is_wall(game, player->pos.y - player->dir.y, player->pos.x - player->dir.x))
	{
		player->pos.y -= player->dir.y;
		player->pos.x -= player->dir.x;
		player->square.y = player->pos.y / game->mlx->minimap->elem_size;
		player->square.x = player->pos.x / game->mlx->minimap->elem_size;
	}
}

void	move_left(t_game *game, t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	(void)game;
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x - player->dir.y;
	player->dir.y = old_dir_x + player->dir.y;
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x - player->plane.y;
	player->plane.y = old_plane_x + player->plane.y;
}

void	move_right(t_game *game, t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	(void)game;
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x - player->dir.y;
	player->dir.y = old_dir_x + player->dir.y;
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x - player->plane.y;
	player->plane.y = old_plane_x + player->plane.y;
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_RIGHT || keycode == KEY_D)
		move_right(game, game->player);
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		move_left(game, game->player);
	else if (keycode == KEY_UP || keycode == KEY_W)
		move_up(game, game->player);
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		move_down(game, game->player);
	else if (keycode == KEY_ESC)
		close_window(game);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:52:35 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 21:03:06 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_game *game, t_player *player)
{
	double	x;
	double	y;

	x = (player->square.x + player->dir.x * player->speed.move);
	y = (player->square.y + player->dir.y * player->speed.move);
	if (game->map->content[(int)y][(int)x] != '1')
	{
		draw_player(game, game->mlx->img_minimap, player->pos, HEX_BLACK);
		player->square.y += player->dir.y * player->speed.move;
		player->square.x += player->dir.x * player->speed.move;
		player->pos.y = player->square.y * game->mlx->minimap->elem_size;
		player->pos.x = player->square.x * game->mlx->minimap->elem_size;
	}
}

void	move_down(t_game *game, t_player *player)
{
	double	x;
	double	y;

	x = (player->square.x - player->dir.x * player->speed.move);
	y = (player->square.y - player->dir.y * player->speed.move);
	if (game->map->content[(int)y][(int)x] != '1')
	{
		draw_player(game, game->mlx->img_minimap, player->pos, HEX_BLACK);
		player->square.y -= player->dir.y * player->speed.move;
		player->square.x -= player->dir.x * player->speed.move;
		player->pos.y = player->square.y * game->mlx->minimap->elem_size;
		player->pos.x = player->square.x * game->mlx->minimap->elem_size;
	}
}

void	move_left(t_game *game, t_player *player)
{
	double	x;
	double	y;

	x = player->square.x + player->dir.y * player->speed.move;
	y = player->square.y - player->dir.x * player->speed.move;
	if (game->map->content[(int)y][(int)x] != '1')
	{
		draw_player(game, game->mlx->img_minimap, player->pos, HEX_BLACK);
		player->square.y -= player->dir.x * player->speed.move;
		player->square.x += player->dir.y * player->speed.move;
		player->pos.y = player->square.y * game->mlx->minimap->elem_size;
		player->pos.x = player->square.x * game->mlx->minimap->elem_size;
	}
}

void	move_right(t_game *game, t_player *player)
{
	double	x;
	double	y;

	x = player->square.x - player->dir.y * player->speed.move;
	y = player->square.y + player->dir.x * player->speed.move;
	if (game->map->content[(int)y][(int)x] != '1')
	{
		draw_player(game, game->mlx->img_minimap, player->pos, HEX_BLACK);
		player->square.y += player->dir.x * player->speed.move;
		player->square.x -= player->dir.y * player->speed.move;
		player->pos.y = player->square.y * game->mlx->minimap->elem_size;
		player->pos.x = player->square.x * game->mlx->minimap->elem_size;
	}
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_D)
		move_right(game, game->player);
	else if (keycode == KEY_RIGHT)
		rotate_right(game, game->player);
	else if (keycode == KEY_A)
		move_left(game, game->player);
	else if (keycode == KEY_LEFT)
		rotate_left(game, game->player);
	else if (keycode == KEY_W)
		move_up(game, game->player);
	else if (keycode == KEY_UP)
		rotate_up(game, game->player);
	else if (keycode == KEY_S)
		move_down(game, game->player);
	else if (keycode == KEY_DOWN)
		rotate_down(game, game->player);
	else if (keycode == KEY_ESC)
		close_window(game);
	return (EXIT_SUCCESS);
}

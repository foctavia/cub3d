/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:52:35 by owalsh            #+#    #+#             */
/*   Updated: 2022/12/01 15:40:35 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_game *game, t_player *player)
{
	double	x;
	double	y;

	x = (player->square.x + player->dir.x * player->speed.move);
	y = (player->square.y + player->dir.y * player->speed.move);
	if (player->move.up && game->map->content[(int)y][(int)x] != '1')
	{
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
	if (player->move.down && game->map->content[(int)y][(int)x] != '1')
	{
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
	if (player->move.left && game->map->content[(int)y][(int)x] != '1')
	{
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
	if (player->move.right && game->map->content[(int)y][(int)x] != '1')
	{
		player->square.y += player->dir.x * player->speed.move;
		player->square.x -= player->dir.y * player->speed.move;
		player->pos.y = player->square.y * game->mlx->minimap->elem_size;
		player->pos.x = player->square.x * game->mlx->minimap->elem_size;
	}
}

int	player_move(t_game *game, t_player *player)
{
	(void)player;
	move_right(game, game->player);
	rotate_right(game, game->player);
	move_left(game, game->player);
	rotate_left(game, game->player);
	move_up(game, game->player);
	rotate_up(game, game->player);
	move_down(game, game->player);
	rotate_down(game, game->player);
	return (EXIT_SUCCESS);
}

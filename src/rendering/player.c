/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:30:33 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/29 16:03:38 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_player_pos(t_game *game, t_elem elem, char c)
{
	int		radius;

	radius = game->mlx->minimap->elem_size / 2;
	game->player->pos.x = elem.x + radius;
	game->player->pos.y = elem.y + radius;
	game->player->square.x = game->player->pos.x
		/ game->mlx->minimap->elem_size;
	game->player->square.y = game->player->pos.y
		/ game->mlx->minimap->elem_size;
	game->player->speed.move = 0.1;
	game->player->speed.rotation = 0.033 * 1.8;
	if (c == NORTH_DIR)
	{
		game->player->dir.x = 0;
		game->player->dir.y = -1;
		game->player->plane.x = 0.66;
		game->player->plane.y = 0;
	}
	else if (c == SOUTH_DIR)
	{
		game->player->dir.x = 0;
		game->player->dir.y = 1;
		game->player->plane.x = -0.66;
		game->player->plane.y = 0.00;
	}
	else if (c == WEST_DIR)
	{
		game->player->dir.x = -1;
		game->player->dir.y = 0;
		game->player->plane.x = 0;
		game->player->plane.y = -0.66;
	}
	else if (c == EAST_DIR)
	{
		game->player->dir.x = 1;
		game->player->dir.y = 0;
		game->player->plane.x = 0;
		game->player->plane.y = 0.66;
	}
}

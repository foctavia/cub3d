/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:30:33 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 18:46:20 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_dir_horizontal(t_player *player, int c)
{
	if (c == WEST_DIR)
	{
		player->dir.x = -1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = -0.66;
	}
	else if (c == EAST_DIR)
	{
		player->dir.x = 1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = 0.66;
	}
}

static void	set_player_dir_vertical(t_player *player, int c)
{
	if (c == NORTH_DIR)
	{
		player->dir.x = 0;
		player->dir.y = -1;
		player->plane.x = 0.66;
		player->plane.y = 0;
	}
	else if (c == SOUTH_DIR)
	{
		player->dir.x = 0;
		player->dir.y = 1;
		player->plane.x = -0.66;
		player->plane.y = 0.00;
	}
}

void	set_player_data(t_game *game, t_player *player,
	t_elem elem, char c)
{
	int		radius;

	radius = game->mlx->minimap->elem_size / 2;
	player->pos.x = elem.x + radius;
	player->pos.y = elem.y + radius;
	player->square.x = player->pos.x
		/ game->mlx->minimap->elem_size;
	player->square.y = player->pos.y
		/ game->mlx->minimap->elem_size;
	player->speed.move = 0.1;
	player->speed.rotation = 0.033 * 1.8;
	set_player_dir_horizontal(player, c);
	set_player_dir_vertical(player, c);
}

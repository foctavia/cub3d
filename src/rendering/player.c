/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:30:33 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/20 13:06:09 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	assign_player_pos(t_game *game, t_elem elem, char c)
{
	int		radius;

	radius = game->mlx->elem_size / 2;
	game->player->pos.x = elem.x + radius;
	game->player->pos.y = elem.y + radius;
	if (c == NORTH_DIR)
		game->player->dir = UP;
	else if (c == SOUTH_DIR)
		game->player->dir = DOWN;
	else if (c == WEST_DIR)
		game->player->dir = LEFT;
	else if (c == EAST_DIR)
		game->player->dir = RIGHT;
	game->player->delta_x = cos(game->player->dir) * 5;
	game->player->delta_y = sin(game->player->dir) * 5;
	return (TRUE);
}

int	change_player_dir(t_player *player, int key)
{
	if (key == KEY_LEFT)
	{
		player->dir -= 0.1;
		if (player->dir < 0)
			player->dir += 2 * M_PI;
		player->delta_x = cos(player->dir) * 5;
		player->delta_y = sin(player->dir) * 5;
	}
	else if (key == KEY_RIGHT)
	{
		(player->dir) += 0.1;
		if (player->dir > 2 * M_PI)
			(player->dir) -= 2 * M_PI;
		player->delta_x = cos(player->dir) * 5;
		player->delta_y = sin(player->dir) * 5;
	}
	return (EXIT_SUCCESS);
}

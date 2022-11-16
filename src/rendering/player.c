/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:30:33 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/16 16:34:43 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	assign_player_pos(t_game *game, char c)
{
	if (c == NORTH_DIR)
		game->player->dir = UP;
	else if (c == SOUTH_DIR)
		game->player->dir = DOWN;
	else if (c == WEST_DIR)
		game->player->dir = LEFT;
	else if (c == EAST_DIR)
		game->player->dir = RIGHT;
	return (TRUE);
}

void	change_player_dir(t_player *player, int key)
{
	if (key == KEY_RIGHT || key == KEY_D)
	{
		if (player->dir == LEFT)
			player->dir = UP;
		else
			player->dir += 90;
	}
	else if (key == KEY_LEFT || key == KEY_A)
	{
		if (player->dir == UP)
			player->dir = LEFT;
		else
			player->dir -= 90;
	}
}

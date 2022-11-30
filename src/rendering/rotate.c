/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:33:18 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 20:37:24 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_up(t_game *game, t_player *player)
{
	player->pitch += game->mlx->height / 2 * player->speed.move;
	if (player->pitch > game->mlx->height / 4)
		player->pitch = game->mlx->height / 4;
}

void	rotate_down(t_game *game, t_player *player)
{
	player->pitch -= game->mlx->height / 2 * player->speed.move;
	if (player->pitch < -game->mlx->height / 4)
		player->pitch = -game->mlx->height / 4;
}

void	rotate_right(t_game *game, t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	(void)game;
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(player->speed.rotation)
		- player->dir.y * sin(player->speed.rotation);
	player->dir.y = old_dir_x * sin(player->speed.rotation)
		+ player->dir.y * cos(player->speed.rotation);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(player->speed.rotation)
		- player->plane.y * sin(player->speed.rotation);
	player->plane.y = old_plane_x * sin(player->speed.rotation)
		+ player->plane.y * cos(player->speed.rotation);
}

void	rotate_left(t_game *game, t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	(void)game;
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(-player->speed.rotation)
		- player->dir.y * sin(-player->speed.rotation);
	player->dir.y = old_dir_x * sin(-player->speed.rotation)
		+ player->dir.y * cos(-player->speed.rotation);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(-player->speed.rotation)
		- player->plane.y * sin(-player->speed.rotation);
	player->plane.y = old_plane_x * sin(-player->speed.rotation)
		+ player->plane.y * cos(-player->speed.rotation);
}

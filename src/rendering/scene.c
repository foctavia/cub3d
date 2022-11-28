/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:19:43 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/28 14:21:27 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_and_ceiling(t_game *game, t_img *img_3d)
{
	t_coord	coord;
	int		x;
	int		y;

	y = 0;
	(void)img_3d;
	while (y < game->mlx->height / 2)
	{
		x = 0;
		while (x < game->mlx->width)
		{
			coord.x = x;
			coord.y = y;
			game->mlx->buffer[y][x] = game->map->ceiling->color;
			// put_pixel(game, img_3d, coord, game->map->ceiling->color);
			x++;
		}
		y++;
	}
	while (y < game->mlx->height)
	{
		x = 0;
		while (x < game->mlx->width)
		{
			coord.x = x;
			coord.y = y;
			game->mlx->buffer[y][x] = game->map->floor->color;
			// put_pixel(game, img_3d, coord, game->map->floor->color);
			x++;
		}
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:19:43 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 18:55:02 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_and_ceiling(t_game *game, t_img img_3d)
{
	t_coord	coord;
	int		x;
	int		y;

	y = 0;
	while (y < game->mlx->height)
	{
		coord.y = y;
		x = 0;
		while (x < game->mlx->width)
		{
			coord.x = x;
			if (y < game->mlx->height / 2)
				put_pixel(game, img_3d, coord, game->map->ceiling->hex);
			else
				put_pixel(game, img_3d, coord, game->map->floor->hex);
			x++;
		}
		y++;
	}
}

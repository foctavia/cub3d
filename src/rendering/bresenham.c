/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:26:35 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/22 17:37:41 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bresenham_wall(t_game *game, t_coord coord1, t_coord coord2, int color)
{
	float	d_x;
	float	d_y;
	int		max;

	d_x = coord2.x - coord1.x;
	d_y = coord2.y - coord1.y;
	max = BIGGER(ABS(d_x), ABS(d_y));
	d_x /= max;
	d_y /= max;
	while ((int)(coord1.x - coord2.x) || (int)(coord1.y - coord2.y))
	{
		put_pixel(game, game->mlx->img_3d, coord1, color);
		coord1.x += d_x;
		coord1.y += d_y;
	}
}

void	bresenham_pixel(t_game *game, t_coord coord1, t_coord coord2, int color)
{
	float	d_x;
	float	d_y;
	int		max;

	if (!is_pixel_in_window_range(game, coord1) || \
		!is_pixel_in_window_range(game, coord2))
		return ;
	d_x = coord2.x - coord1.x;
	d_y = coord2.y - coord1.y;
	max = BIGGER(ABS(d_x), ABS(d_y));
	d_x /= max;
	d_y /= max;
	while ((int)(coord1.x - coord2.x) || (int)(coord1.y - coord2.y))
	{
		put_pixel(game, game->mlx->img_minimap, coord1, color);
		coord1.x += d_x;
		coord1.y += d_y;
	}
}

void	bresenham(t_game *game, t_coord coord1, t_coord coord2, int color)
{
	float	d_x;
	float	d_y;
	int		max;

	coord1.x = (float)(coord1.x * game->mlx->minimap->elem_size);
	coord1.y = (float)(coord1.y * game->mlx->minimap->elem_size);
	coord2.x = (float)(coord2.x * game->mlx->minimap->elem_size);
	coord2.y = (float)(coord2.y * game->mlx->minimap->elem_size);
	d_x = coord2.x - coord1.x;
	d_y = coord2.y - coord1.y;
	max = BIGGER(ABS(d_x), ABS(d_y));
	d_x /= max;
	d_y /= max;
	while ((int)(coord1.x - coord2.x) || (int)(coord1.y - coord2.y))
	{
		put_pixel(game, game->mlx->img_minimap, coord1, color);
		coord1.x += d_x;
		coord1.y += d_y;
	}
}

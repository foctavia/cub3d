/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:09:13 by foctavia          #+#    #+#             */
/*   Updated: 2022/11/14 12:45:19 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bresenham(t_game *game, t_img *img, float x1, float y1, float x2, float y2, int color, t_elem elem)
{
	float	d_x;
	float	d_y;
	int		max;

	x1 *= elem.side;
	x2 *= elem.side;
	y1 *= elem.side;
	y2 *= elem.side;
	d_x = x2 - x1;
	d_y = y2 - y1;
	max = BIGGER(ABS(d_x), ABS(d_y));
	d_x /= max;
	d_y /= max;
	while ((int)(x1 - x2) || (int)(y1 - y2))
	{
		my_mlx_pixel_put(game, img, x1, y1, color);
		x1 += d_x;
		y1 += d_y;
	}
}

void	draw_line(t_game *game, t_img *img, t_elem elem, int x, int y, int color)
{
	if (x < game->map->width)
		bresenham(game, img, x, y, x + 1, y, color, elem);
	if (y < game->map->height)
		bresenham(game, img, x, y, x, y + 1, color, elem);
}

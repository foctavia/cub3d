/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:09:13 by foctavia          #+#    #+#             */
/*   Updated: 2022/11/10 18:18:26 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	bresenham(t_game *game, t_img *img, float x1, float y1, float x2, float y2)
{
	float	d_x;
	float	d_y;
	int		max;

	(void)game;
	x1 *= 32;
	x2 *= 32;
	y1 *= 32;
	y2 *= 32;
	d_x = x2 - x1;
	d_y = y2 - y1;
	max = BIGGER(ABS(d_x), ABS(d_y));
	d_x /= max;
	d_y /= max;
	while ((int)(x1 - x2) || (int)(y1 - y2))
	{
		my_mlx_pixel_put(img, x1, y1, 0x00FF0000);
		x1 += d_x;
		y1 += d_y;
	}
}

void	draw(t_game *game, t_img *img, int x, int y)
{
	if (x < game->map->width - 1)
		bresenham(game, img, x, y, x + 1, y);
	if (y < game->map->height - 1)
		bresenham(game, img, x, y, x, y + 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:09:13 by foctavia          #+#    #+#             */
/*   Updated: 2022/11/12 19:17:59 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



// void	bresenham(t_game *game, t_img *img, float x1, float y1, float x2, float y2, int color)
// {
// 	float	d_x;
// 	float	d_y;
// 	int		max;
// 	int		big;

// 	if (game->map->height > game->map->width)
// 		big = game->mlx->height / game->map->height;
// 	else
// 		big = game->mlx->width / game->map->width;
// 	x1 *= big;
// 	x2 *= big;
// 	y1 *= big;
// 	y2 *= big;
// 	d_x = x2 - x1;
// 	d_y = y2 - y1;
// 	max = BIGGER(ABS(d_x), ABS(d_y));
// 	d_x /= max;
// 	d_y /= max;
// 	while ((int)(x1 - x2) || (int)(y1 - y2))
// 	{
// 		my_mlx_pixel_put(img, x1, y1, color);
// 		x1 += d_x;
// 		y1 += d_y;
// 	}
// }

// void	draw(t_game *game, t_img *img, int x, int y, int color)
// {
// 	if (x < game->map->width)
// 		bresenham(game, img, x, y, x + 1, y, color);
// 	if (y < game->map->height)
// 		bresenham(game, img, x, y, x, y + 1, color);
// }

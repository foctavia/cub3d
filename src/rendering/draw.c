/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:09:13 by foctavia          #+#    #+#             */
/*   Updated: 2022/11/30 18:55:37 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_game *game, t_img img, t_coord coord, int color)
{
	char	*dst;

	if (coord.x > game->mlx->width || \
		coord.y > game->mlx->height)
		return ;
	dst = img.addr + ((int)coord.y * img.line_length \
		+ (int)coord.x * (img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_lines(t_game *game)
{
	t_coord	coord1;
	t_coord	coord2;

	coord1.y = 0;
	while (coord1.y < game->map->height)
	{
		coord1.x = 0;
		while (coord1.x < game->map->width)
		{
			if (coord1.x < game->map->width)
			{
				coord2.x = coord1.x + 1;
				coord2.y = coord1.y;
				bresenham(game, coord1, coord2, HEX_GREEN);
			}
			if (coord1.y < game->map->height)
			{
				coord2.x = coord1.x;
				coord2.y = coord1.y + 1;
				bresenham(game, coord1, coord2, HEX_GREEN);
			}
			coord1.x++;
		}
		coord1.y++;
	}
}

void	draw_square(t_game *game, t_elem elem, t_img img)
{
	t_coord	index;

	if (game->mlx->window == NULL)
		return ;
	index.x = elem.x;
	while (index.x < elem.x + game->mlx->minimap->elem_size)
	{
		index.y = elem.y;
		while (index.y < elem.y + game->mlx->minimap->elem_size)
		{
			put_pixel(game, img, index, elem.color);
			index.y++;
		}
		index.x++;
	}
}

void	draw_player(t_game *game, t_img img, t_coord dest, int color)
{
	t_coord	center;
	int		radius;
	double	i;
	double	x;
	double	y;

	radius = game->mlx->minimap->elem_size / 2;
	i = 0;
	while (i < 360)
	{
		x = radius * 0.1 * cos(i * M_PI / 180);
		y = radius * 0.1 * sin(i * M_PI / 180);
		center.x = dest.x + x;
		center.y = dest.y + y;
		put_pixel(game, img, center, color);
		i += 0.01;
	}
}

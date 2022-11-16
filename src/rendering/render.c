/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:47:10 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/16 17:43:26 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_player(t_game *game, t_img *img, t_coord dest, int color)
{
	t_coord	center;
	int		radius;
	double	i;
	double	x;
	double	y;

	radius = game->mlx->elem_size / 2;
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

void	render_minimap(t_game *game, t_map *map, t_img *img, t_player *player)
{
	int		x;
	int		y;
	t_elem	elem;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			elem.x = x * game->mlx->elem_size;
			elem.y = y * game->mlx->elem_size;
			if (map->content[y][x] == GROUND)
				elem.color = HEX_BLACK;
			else if (map->content[y][x] == WALL)
				elem.color = HEX_WHITE;
			else if (!player && is_player(map->content[y][x])
				&& assign_player_pos(game, map->content[y][x]))
				put_player(game, elem, img);
			else if (player)
				render_player(game, game->mlx->minimap, player->pos, HEX_RED);
			if (map->content[y][x] != ' ' && !is_player(map->content[y][x]))
				draw_square(game, elem, img);
			x++;
		}
		y++;
	}
	draw_lines(game);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:44 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/21 13:55:50 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_grid_coord(t_game *game, int pixel, int axis)
{
	int	grid;

	grid = 0;
	if (axis == 'x')
		grid = pixel * game->map->width / game->mlx->width;
	else if (axis == 'y')
		grid = pixel * game->map->height / game->mlx->height;
	return (grid);
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
		put_pixel(game, game->mlx->minimap, coord1, color);
		coord1.x += d_x;
		coord1.y += d_y;
	}
}

float	get_distance(t_coord coord1, t_coord coord2, float angle)
{
	float	res;

	(void)angle;
	res = sqrt(((coord2.x - coord1.x) * (coord2.x - coord1.x)) \
		+ ((coord2.y - coord1.y) * (coord2.y - coord1.y)));
	return (res);
}

void	draw_ray(t_game *game, t_player *player, float ray_dir)
{
	float	hor_dist;
	float	ver_dist;
	t_coord	hor_ray;
	t_coord	ver_ray;

	hor_ray = get_horizontal_ray(game, player, ray_dir);
	ver_ray = get_vertical_ray(game, player, ray_dir);
	hor_dist = get_distance(player->pos, hor_ray, player->dir);
	ver_dist = get_distance(player->pos, ver_ray, player->dir);
	if ((hor_dist && hor_dist < ver_dist) || !ver_dist)
		bresenham_pixel(game, player->pos, hor_ray, HEX_RED);
	else if ((ver_dist && ver_dist < hor_dist) || !hor_dist)
		bresenham_pixel(game, player->pos, ver_ray, HEX_RED);
}

void	ft_raycast(t_game *game, t_player *player)
{
	float	i;
	float	ray_dir;

	i = 0;
	ray_dir = player->dir - DEGREE_RADIAN * 30;
	if (ray_dir < 0)
		ray_dir += 2 * PI;
	else if (ray_dir > 2 * PI)
		ray_dir -= 2 * PI;
	while (i < 60)
	{
		draw_ray(game, player, ray_dir);
		ray_dir += DEGREE_RADIAN;
		i++;
	}
}

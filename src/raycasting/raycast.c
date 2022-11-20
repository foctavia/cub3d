/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:44 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/20 13:04:23 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// t_coord	get_grid_coord(t_game *game, t_coord *pixel)
// {
// 	t_coord	grid;

// 	grid.x = pixel->x * game->map->width / game->mlx->width;
// 	grid.y = pixel->y * game->map->height / game->mlx->height;
// 	return (grid);
// }

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

int	is_pixel_in_window_range(t_game *game, t_coord coord)
{
	if (coord.x < 0 || coord.x > game->mlx->width)
		return (FALSE);
	if (coord.y < 0 || coord.y > game->mlx->height)
		return (FALSE);
	return (TRUE);	
}

void	bresenham_pixel(t_game *game, t_coord coord1, t_coord coord2, int color)
{
	float	d_x;
	float	d_y;
	int		max;

	if (!is_pixel_in_window_range(game, coord1) ||
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

void	ft_raycast(t_game *game, t_mlx *mlx, t_player *player)
{
	float	i;
	float	hor_dist;
	float	ver_dist;
	t_coord	hor_ray;
	t_coord	ver_ray;
	
	(void)mlx;
	i = 0;
	hor_ray = get_horizontal_ray(game, player, i);
	ver_ray = get_vertical_ray(game, player, i);
	hor_dist = get_distance(player->pos, hor_ray, player->dir);
	ver_dist = get_distance(player->pos, ver_ray, player->dir);
	// printf("hor_dist : %f && ver_dist : %f\n", hor_dist, ver_dist);
	if ((hor_dist && hor_dist < ver_dist) || !ver_dist)
		bresenham_pixel(game, player->pos, hor_ray, HEX_RED);
	else if ((ver_dist && ver_dist < hor_dist) || !hor_dist)
		bresenham_pixel(game, player->pos, ver_ray, HEX_RED);
	// if (ver_dist)
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:44 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/23 14:01:09 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_grid_coord(t_game *game, int pixel, int axis)
{
	int	grid;

	grid = 0;
	if (axis == 'x')
		grid = pixel * game->map->width / game->mlx->minimap->width;
	else if (axis == 'y')
		grid = pixel * game->map->height / game->mlx->minimap->height;
	return (grid);
}

float	get_distance(t_coord coord1, t_coord coord2, float angle)
{
	float	res;

	(void)angle;
	res = sqrt(((coord2.x - coord1.x) * (coord2.x - coord1.x)) \
		+ ((coord2.y - coord1.y) * (coord2.y - coord1.y)));
	return (res);
}

float	draw_ray(t_game *game, t_player *player, float ray_dir)
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
	{
		bresenham_pixel(game, player->pos, hor_ray, HEX_RED);
		return (hor_dist);
	}
	else if ((ver_dist && ver_dist < hor_dist) || !hor_dist)
	{
		bresenham_pixel(game, player->pos, ver_ray, HEX_RED);
		return (ver_dist);
	}
	return (ver_dist);
}

void	draw_walls(t_game *game, t_camera *camera, float ray_length, float i)
{
	t_coord	start;
	t_coord	end;
	float	line_offset;
	float	line_height;
	int		j;

	line_height = (game->mlx->minimap->elem_size * \
		game->mlx->minimap->width) / ray_length;
	if (line_height > camera->height)
		line_height = camera->height;
	line_offset = camera->center.y - (line_height / 2);
	start.y = line_offset;
	end.y = line_offset + line_height;
	j = 0;
	while (j < game->mlx->width / game->camera->fov)
	{
		start.x = i + j;
		end.x = i + j;
		draw_texture(game, start, end, HEX_WALLS);
		j++;
	}
}

void	ft_raycast(t_game *game, t_player *player)
{
	float	ray_dir;
	float	ray_length;
	float	ray_offset;
	float	i;

	ray_dir = player->dir - DEGREE_RADIAN * 30;
	put_angle_in_range(&ray_dir);
	i = 0;
	while (i < game->mlx->width)
	{
		ray_offset = player->dir - ray_dir;
		put_angle_in_range(&ray_offset);
		ray_length = draw_ray(game, player, ray_dir);
		ray_length *= cos(ray_offset);
		draw_walls(game, game->camera, ray_length, i);
		ray_dir += DEGREE_RADIAN;
		i += game->mlx->width / game->camera->fov;
	}
}

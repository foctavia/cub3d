/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:44 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/24 11:52:14 by foctavia         ###   ########.fr       */
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

void	draw_walls(t_game *game, float ray_length, float i)
{
	t_coord	start;
	t_coord	end;
	float	line_offset;
	float	line_height;
	int		j;

	line_height = (game->mlx->minimap->elem_size * \
		game->mlx->minimap->width) / ray_length;
	if (line_height > game->mlx->height)
		line_height = game->mlx->height;
	line_offset = (game->mlx->height / 2) - (line_height / 2);
	start.y = line_offset;
	end.y = line_offset + line_height;
	j = 0;
	while (j < game->mlx->width / FOV)
	{
		start.x = i + j;
		end.x = i + j;
		bresenham_wall(game, start, end, HEX_WALLS);
		j++;
	}
}

void	ft_raycast(t_game *game, t_player *player)
{
	t_coord dir;
	t_coord	plane;
	t_coord	raydir;
	t_coord	map;
	t_coord	side_dist;
	t_coord	delta_dist;
	double	perpwalldist;
	double	camera_x;
	double	time;
	double	old_time;
	int		hit;
	int		side;
	int		x;

	time = 0;
	old_time = 0;
	map.x = player->pos.x;
	map.y = player->pos.y;
	dir.x = -1;
	dir.y = 0;
	plane.x = 0;
	plane.y = 0.66;
	x = 0;
	while (x < game->map->width)
	{
		camera_x = 2 * x / 0

	}
}

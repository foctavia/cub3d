/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:44 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/28 17:57:47 by owalsh           ###   ########.fr       */
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

int	is_wall_hihi(t_game *game, float dest_x, float dest_y)
{
	float	square_x;
	float	square_y;

	square_y = dest_y;
	square_x = dest_x;
	if ((int)square_y < 0 || (int)square_x < 0 || \
		(int)square_y >= game->map->height || (int)square_x >= game->map->width)
		return (FALSE);
	if (game->map->content[(int)square_y][(int)square_x] == WALL)
		return (TRUE);
	return (FALSE);
}

void	ft_raycast(t_game *game, t_player *player)
{
	t_coord dir;
	t_coord	plane;

	t_coord	raydir;
	t_coord	map;
	t_coord	side_dist;
	t_coord	pos;
	t_coord	delta_dist;
	t_coord step;
	double	perpwalldist;
	double	camera_x;
	double	time;
	double	old_time;
	int		hit;
	int		side;
	int		x;
	int		line_height;
	int		draw_start;
	int		draw_end;

	time = 0;
	old_time = 0;


	pos.x = player->pos.x / game->mlx->minimap->elem_size;
	pos.y = player->pos.y / game->mlx->minimap->elem_size;
	
	if (game->map->content[(int)pos.y][(int)pos.x] == 'E')
	{
		dir.x = 0;
		dir.y = 1;
		plane.x = 0.66;
		plane.y = 0.0;
	}
	if (game->map->content[(int)pos.y][(int)pos.x] == 'W')
	{
		dir.x = 0;
		dir.y = -1;
		plane.x = -0.66;
		plane.y = 0.00;
	}
	if (game->map->content[(int)pos.y][(int)pos.x] == 'N')
	{
		dir.x = -1;
		dir.y = 0;
		plane.x = 0.0;
		plane.y = 0.66;
	}
	if (game->map->content[(int)pos.y][(int)pos.x] == 'S')
	{
		dir.x = 1;
		dir.y = 0;
		plane.x = 0.0;
		plane.y = -0.66;
	}
	// dir.x = -1;
	// dir.y = 0;
	// plane.x = 0;
	// plane.y = 0.66;
	x = 0;
	while (x < game->mlx->width )
	{

		map.x = pos.x;
		map.y = pos.y;
		camera_x = 2 * x / (double)game->mlx->width - 1;
		raydir.x = dir.x + plane.x * camera_x;
		raydir.y = dir.y + plane.y * camera_x;

		delta_dist.x = fabs(1 / raydir.x);
		delta_dist.y = fabs(1 / raydir.y);

		hit = 0;
		
		if (raydir.x < 0)
		{
			step.x = -1;
			side_dist.x = (pos.x - map.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (map.x + 1 - (pos.x)) * delta_dist.x;
		}
		if (raydir.y < 0)
		{
			step.y = -1;
			side_dist.y = (pos.y - map.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (map.y + 1 - pos.y) * delta_dist.y;
		}
			
		while (hit == 0)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step.y;
				side = 1;
			}
			if (is_wall_hihi(game, map.x, map.y))
				hit = 1;
		}
		
		if (side == 0)
			perpwalldist = (side_dist.x - delta_dist.x);
		else
			perpwalldist = (side_dist.y - delta_dist.y);

		// if (side == 0)
		// 	perpwalldist = (map.x - pos.x + (1 - step.x) / 2) / dir.x;
		// else
		// 	perpwalldist = (map.y - pos.yx + (1 - step.x) / 2) / dir.x;
		
		line_height = (int)(game->mlx->height / perpwalldist);
		
		draw_start = -1 * line_height / 2 + game->mlx->height / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + game->mlx->height / 2;
		if (draw_end >= game->mlx->height)
			draw_end = game->mlx->height - 1;
		
		t_coord coord1;
		t_coord coord2;

		coord1.x = x ;
		coord1.y = draw_start;

		coord2.x = x;
		coord2.y = draw_end;


		bresenham_wall(game, coord1, coord2, HEX_RED);
		x++;

	}
	
}

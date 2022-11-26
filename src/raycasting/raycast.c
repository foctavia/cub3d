/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:44 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/26 21:48:12 by owalsh           ###   ########.fr       */
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

float	draw_ray(t_game *game, t_player *player, t_ray *ray)
{
	float	hor_dist;
	float	ver_dist;
	t_coord	hor_ray;
	t_coord	ver_ray;

	hor_ray = get_horizontal_ray(game, player, ray->dir);
	ver_ray = get_vertical_ray(game, player, ray->dir);
	hor_dist = get_distance(player->pos, hor_ray, player->dir);
	ver_dist = get_distance(player->pos, ver_ray, player->dir);
	if ((hor_dist && hor_dist < ver_dist) || !ver_dist)
	{
		ray->side = SIDE_X;
		ray->intersect.x = hor_ray.x;
		ray->intersect.y = hor_ray.y;
		bresenham_pixel(game, player->pos, hor_ray, HEX_RED);
		return (hor_dist);
	}
	else if ((ver_dist && ver_dist < hor_dist) || !hor_dist)
	{
		ray->side = SIDE_Y;
		ray->intersect.x = ver_ray.x;
		ray->intersect.y = ver_ray.y;
		bresenham_pixel(game, player->pos, ver_ray, HEX_RED);
		return (ver_dist);
	}
	return (ver_dist);
}


void	draw_walls(t_game *game, t_camera *camera, float i, t_ray ray)
{
	t_coord	start;
	t_coord	end;
	t_img	img;
	float	line_offset;
	float	line_height;
	float	j;
	int		width;
	int		height;
	// int		texture_x;
	// int		texture_y;

	img.img = mlx_xpm_file_to_image(game->mlx->mlx, "eagle.xpm", \
		&width, &height);
	img.addr = mlx_get_data_addr(img.img, \
		&img.bits_per_pixel, &img.line_length, &img.endian);

	line_height = (game->mlx->minimap->elem_size * \
		game->mlx->minimap->width) / ray.length;
	if (line_height > camera->height)
		line_height = camera->height;
	line_offset = camera->center.y - (line_height / 2);
	start.y = line_offset;
	end.y = line_offset + line_height;

	// if (ray.side != SIDE_X)
	// 	return ;
	j = 0;
	while (j < game->mlx->width / game->camera->fov)
	{
		start.x = i + j;
		end.x = i + j;
		
		float wall_x;
		if (ray.side == SIDE_X)
			wall_x = (int)ray.intersect.x % 64;
		else
			wall_x = (int)ray.intersect.y % 64;
		// wall_x -= floor(wall_x);
		
		int tex_x;
		tex_x = wall_x;
		// tex_x = (int)(wall_x * (float)64);
		// if (ray.side == SIDE_X && ray.dir > 0)
		// 	tex_x = 64 - tex_x - 1;
		// else if (ray.side == SIDE_Y && ray.dir < 0)
		// 	tex_x = 64 - tex_x - 1;

		// printf("tex_x = %d\n", tex_x);
		float step = height / line_height;
		float y = start.y;
		float tex_pos = (start.y - game->mlx->height / 2 \
			+ line_height / 2) * step;
		// int tex_y = 0;
		(void)tex_pos;
		while (y < end.y)
		{
			int tex_y = (int)tex_pos & (height - 1);
			// printf("tex_y: %d\n", tex_y);
			// tex_y += step;
			tex_pos += step;
			
			// if (tex_x > 0 && tex_x < width && tex_y > 0 && tex_y < height)
			// {
				game->mlx->img_3d->addr[(int)y * game->mlx->img_3d->line_length + (int)start.x * 4] = \
					img.addr[(tex_y * 64) + (tex_x * 4)];
				game->mlx->img_3d->addr[((int)y * game->mlx->img_3d->line_length + (int)start.x * 4) + 1] = \
					img.addr[((tex_y * 64) + (tex_x * 4)) + 1];
				game->mlx->img_3d->addr[((int)y * game->mlx->img_3d->line_length + (int)start.x * 4) + 2] = \
					img.addr[((tex_y * 64) + (tex_x * 4)) + 2];
				game->mlx->img_3d->addr[((int)y * game->mlx->img_3d->line_length + (int)start.x * 4) + 3] = \
					img.addr[((tex_y * 64) + (tex_x * 4)) + 3];
				
			// }
			
			y += 1;
		}
		// bresenham_wall(game, start, end, HEX_WHITE);
		// draw_texture(game, start, end, line_height, start.y, end.y);
		j++;
	}
}

void	ft_raycast(t_game *game, t_player *player)
{
	t_ray	ray;
	float	i;

	ray.dir = player->dir - DEGREE_RADIAN * 30;
	put_angle_in_range(&ray.dir);
	i = 0;
	while (i < game->mlx->width)
	{
		ray.offset = player->dir - ray.dir;
		put_angle_in_range(&ray.offset);
		ray.length = draw_ray(game, player, &ray);
		ray.length *= cos(ray.offset);
		draw_walls(game, game->camera, i, ray);
		ray.dir += DEGREE_RADIAN;
		i += game->mlx->width / game->camera->fov;
	}
}

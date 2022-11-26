/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:44 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/26 16:10:32 by owalsh           ###   ########.fr       */
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

float	draw_ray(t_game *game, t_player *player, float ray_dir, t_coord *intersect)
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
		intersect->x = hor_ray.x;
		intersect->y = hor_ray.y;
		return (hor_dist);
	}
	else if ((ver_dist && ver_dist < hor_dist) || !hor_dist)
	{
		bresenham_pixel(game, player->pos, ver_ray, HEX_RED);
		intersect->x = ver_ray.x;
		intersect->y = ver_ray.y;
		return (ver_dist);
	}
	return (ver_dist);
}

void	draw_texture(t_game *game, t_img img, t_coord coord, float texture_x, float texture_y)
{

		game->mlx->img_3d->addr[(int)coord.y * \
			game->mlx->img_3d->line_length + (int)coord.x] \
			= img.addr[((int)texture_y * 32) + ((int)texture_x)];
		game->mlx->img_3d->addr[((int)coord.y * \
			game->mlx->img_3d->line_length + (int)coord.x ) + 1] \
			= img.addr[(((int)texture_y * 32) + ((int)texture_x * 4)) + 1];
		game->mlx->img_3d->addr[((int)coord.y * \
			game->mlx->img_3d->line_length + (int)coord.x * 4) + 2] \
			= img.addr[(((int)texture_y * 32) + ((int)texture_x * 4)) + 2];
		game->mlx->img_3d->addr[((int)coord.y * \
			game->mlx->img_3d->line_length + (int)coord.x * 4) + 3] \
			= img.addr[(((int)texture_y * 32) + ((int)texture_x * 4)) + 3];
}

void	draw_walls(t_game *game, float ray_length, float i, t_coord intersect, float ray_dir)
{
	t_coord	start;
	t_coord	end;
	float	line_offset;
	float	line_height;
	int		j;
	t_img	img;
	int		width;
	int 	height;
	float	texture_x;
	float	texture_y;
	

	(void)end;
	img.img = mlx_xpm_file_to_image(game->mlx->mlx, "red.xpm", \
		&width, &height);
	img.addr = mlx_get_data_addr(img.img, \
		&img.bits_per_pixel, &img.line_length, &img.endian);

	line_height = (game->mlx->minimap->elem_size * \
		game->mlx->minimap->width) / ray_length;

	// texture start
	float	texturey_offset;
	float	texturey_step;
	
	texturey_step = 32.0 / (float)line_height;
	texturey_offset = 0;
	
	if (line_height > game->mlx->height)
	{
		texturey_offset = (line_height - game->mlx->height) / 2.0; // added for texture
		line_height = game->mlx->height;
	}
	line_offset = (game->mlx->height / 2) - (line_height / 2);
	start.y = line_offset;
	end.y = line_offset + line_height;

	// part for textures
	texture_y = texturey_offset * texturey_step;
	texture_x = (int)(intersect.x / 2.0) % 32;
	if (ray_dir > 180)
	{
		texture_x = 31 - texture_x;
	}
	
	texture_y+= 32;
	j = 0;
	while (j < game->mlx->width / FOV)
	{
		start.x = i + j;
		end.x = i + j;
		int y = 0;
		while (y < line_height)
		{
			start.y = y + line_offset;
			// put_pixel(game, game->mlx->img_3d, start, HEX_WALLS);
			
			game->mlx->img_3d->addr[(int)start.y * \
			game->mlx->img_3d->line_length + (int)start.x * 4] \
				= img.addr[((int)texture_y * 32) + ((int)texture_x * 4)];
			game->mlx->img_3d->addr[((int)start.y * 
				game->mlx->img_3d->line_length + (int)start.x * 4) + 1] 
				= img.addr[(((int)texture_y * 32) + ((int)texture_x * 4)) + 1];
			game->mlx->img_3d->addr[((int)start.y * 
				game->mlx->img_3d->line_length + (int)start.x * 4) + 2] 
				= img.addr[(((int)texture_y * 32) + ((int)texture_x * 4)) + 2];
			game->mlx->img_3d->addr[((int)start.y * 
				game->mlx->img_3d->line_length + (int)start.x * 4) + 3] 
				= img.addr[(((int)texture_y * 32) + ((int)texture_x * 4)) + 3];
			
			// bresenham_wall(game, start, end, HEX_WALLS);
			
			y++;
			
		}
		j++;
	}
}

void	ft_raycast(t_game *game, t_player *player)
{
	float	ray_dir;
	float	ray_length;
	float	ray_offset;
	float	i;
	t_coord	intersect;

	ray_dir = player->dir - DEGREE_RADIAN * 30;
	put_angle_in_range(&ray_dir);
	i = 0;
	while (i < game->mlx->width)
	{
		ray_offset = player->dir - ray_dir;
		put_angle_in_range(&ray_offset);
		ray_length = draw_ray(game, player, ray_dir, &intersect);
		ray_length *= cos(ray_offset);
		draw_walls(game, ray_length, i, intersect, ray_dir);
		ray_dir += DEGREE_RADIAN;
		i += game->mlx->width / FOV;
	}
}

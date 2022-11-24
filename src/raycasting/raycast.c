/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:44 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/24 18:53:45 by foctavia         ###   ########.fr       */
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

void	draw_texture(t_game *game, t_coord coord1, t_coord coord2, float line_height, float start_y, float end_y)
{
	t_img	img;
	int		width;
	int 	height;
	int		texture_x;
	int		texture_y;
	// double	wall_x;
	double	step;
	double	texture_pos;
	float	d_x;
	float	d_y;
	int		max;
	
	(void)end_y;
	img.img = mlx_xpm_file_to_image(game->mlx->mlx, "eagle.xpm", \
		&width, &height);
	img.addr = mlx_get_data_addr(img.img, \
		&img.bits_per_pixel, &img.line_length, &img.endian);
	game->mlx->texture = &img;
	texture_x = (int)(coord1.x * (double)width);
	step = 1 * height / line_height;
	texture_pos = (start_y - game->mlx->height / 2 + line_height / 2) \
		* step;
	d_x = coord2.x - coord1.x;
	d_y = coord2.y - coord1.y;
	max = BIGGER(ABS(d_x), ABS(d_y));
	d_x /= max;
	d_y /= max;
	while ((int)(coord1.x - coord2.x) || (int)(coord1.y - coord2.y))
	{
	// int j = start_y;
	// while (j < end_y)
	// {
		texture_y = (int)texture_pos & (height - 1);
		texture_pos += step;
		// if ((texture_x * 4 + texture_y * img.line_length + 3 > width * 4 + height * img.line_length) || \
		// 	(coord1.x * 4 + coord1.y * game->mlx->img_3d->line_length > game->mlx->width * 4 + game->mlx->height * game->mlx->img_3d->line_length) || \
		// 	(coord1.x < 0 || coord1.y < 0 || texture_x < 0 || texture_y < 0))
		// 	return ;
		
		// if (coord1.y > height || coord1.x > width)
		// 	return ;
		// int color = *(unsigned int *)(img.addr + (texture_y * height + texture_x));
		game->mlx->img_3d->addr[(int)coord1.y * game->mlx->img_3d->line_length + (int)coord1.x * 4] = \
			img.addr[(texture_y * height) + (texture_x * 4)];
		game->mlx->img_3d->addr[((int)coord1.y * game->mlx->img_3d->line_length + (int)coord1.x * 4) + 1] = \
			img.addr[((texture_y * height) + (texture_x * 4)) + 1];
		game->mlx->img_3d->addr[((int)coord1.y * game->mlx->img_3d->line_length + (int)coord1.x * 4) + 2] = \
			img.addr[((texture_y * height) + (texture_x * 4)) + 2];
		game->mlx->img_3d->addr[((int)coord1.y * game->mlx->img_3d->line_length + (int)coord1.x * 4) + 3] = \
			img.addr[((texture_y * height) + (texture_x * 4)) + 3];
		// put_pixel(game, game->mlx->img_3d, coord1, whatev);
		coord1.x += d_x;
		coord1.y += d_y;
		
	// 	j++;
	// }
	}
}

void	draw_walls(t_game *game, t_camera *camera, float ray_length, float i)
{
	t_coord	start;
	t_coord	end;
	float	line_offset;
	float	line_height;
	float		j;

	(void)i;
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
		// bresenham_wall(game, start, end, HEX_WHITE);
		draw_texture(game, start, end, line_height, start.y, end.y);
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

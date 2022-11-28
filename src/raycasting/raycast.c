/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:44 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/27 18:57:42 by owalsh           ###   ########.fr       */
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
		// ray
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

// void	draw_texture(t_game *game, t_img img,  t_coord coord, t_coord texture)
// {

	
// }

void	compute_texture_data(t_texture *texture, t_ray ray)
{
	texture->pos.y = texture->offset * texture->step;
	if (ray.side == SIDE_X)
	{
		texture->pos.x = (int)ray.intersect.x % 64;
		if (is_looking_down(ray.dir))
			texture->pos.x = 64 - texture->pos.x;
	}
	if (ray.side == SIDE_Y)
	{
		texture->pos.x = (int)ray.intersect.y % 64;
		if (is_looking_left(ray.dir))
			texture->pos.x = 64 - texture->pos.x;
	}
}

void	draw_walls(t_game *game, float i, t_ray ray)
{
	t_texture	texture;
	t_coord		coord;
	float		line_offset;
	float		line_height;
	float		j;
	t_img		img;
	int			width;
	int			height;

	img.img = mlx_xpm_file_to_image(game->mlx->mlx, "eagle.xpm", \
		&width, &height);
	img.addr = mlx_get_data_addr(img.img, \
		&img.bits_per_pixel, &img.line_length, &img.endian);

	line_height = (game->mlx->minimap->elem_size * \
		game->mlx->minimap->width) / ray.length;
	line_offset = (WINDOW_H / 2) - (line_height / 2);
	
	texture.step = 64 / (float)line_height;
	texture.offset = 0;
	if (line_height > WINDOW_H)
	{
		texture.offset = (line_height - game->mlx->height) / 2;
		line_height = WINDOW_H;
	}

	j = 0;
	while (j < game->mlx->width / FOV)
	{
		compute_texture_data(&texture, ray);
		coord.x = i + j;
		coord.y = line_offset;
		while (coord.y < line_offset + line_height)
		{
			game->mlx->img_3d->addr[(int)coord.y * game->mlx->img_3d->line_length 
				+ (int)coord.x * 4] 
				= img.addr[((int)texture.pos.y * 64) + ((int)texture.pos.x * 4)];
			game->mlx->img_3d->addr[((int)coord.y * game->mlx->img_3d->line_length
				+ (int)coord.x * 4) + 1]
				= img.addr[(((int)texture.pos.y * 64) + ((int)texture.pos.x * 4)) + 1];
			game->mlx->img_3d->addr[((int)coord.y * game->mlx->img_3d->line_length 
				+ (int)coord.x * 4) + 2]
				= img.addr[(((int)texture.pos.y * 64) + ((int)texture.pos.x * 4)) + 2];
			game->mlx->img_3d->addr[((int)coord.y * game->mlx->img_3d->line_length
				+ (int)coord.x * 4) + 3]
				= img.addr[(((int)texture.pos.y * 64) + ((int)texture.pos.y * 4)) + 3];

			coord.y += 1;
			texture.pos.y += texture.step;
		}
		j++;
	}
	mlx_destroy_image(game->mlx->mlx, img.img);
}

void	ft_raycast(t_game *game, t_player *player)
{
	t_ray	ray;
	float	i;

	ray.dir = player->dir - (DEGREE_RADIAN * 30);
	put_angle_in_range(&ray.dir);
	i = 0;
	while (i < game->mlx->width)
	{
		ray.offset = player->dir - ray.dir;
		put_angle_in_range(&ray.offset);
		ray.length = draw_ray(game, player, &ray);
		ray.length *= cos(ray.offset);
		draw_walls(game, i, ray);
		ray.dir += DEGREE_RADIAN;
		i += game->mlx->width / FOV;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:44 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 12:29:51 by owalsh           ###   ########.fr       */
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

int	is_wall(t_game *game, double square_x, double square_y)
{
	if ((int)square_y < 0 || (int)square_x < 0 || \
		(int)square_y >= game->map->height || (int)square_x >= game->map->width)
		return (FALSE);
	if (game->map->content[(int)square_y][(int)square_x] == WALL)
		return (TRUE);
	return (FALSE);
}

void	init_ray(t_game *game, t_ray *ray, t_player *player, int x)
{
	ray->hit = 0;
	ray->map.x = (int)player->square.x;
	ray->map.y = (int)player->square.y;
	ray->camera_x = 2 * x / (double)game->mlx->width - 1;
	ray->dir.x = player->dir.x + player->plane.x * ray->camera_x;
	ray->dir.y = player->dir.y + player->plane.y * ray->camera_x;
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	ray->delta_dist.x = fabs(1 / ray->dir.x);
}

void	init_dda_vector(t_ray *ray, t_player *player)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player->square.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1 - player->square.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player->square.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y  + 1 - player->square.y) * ray->delta_dist.y;
	}
}

void	run_dda(t_ray *ray, t_game *game)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = SIDE_Y;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = SIDE_X;
		}
		if (is_wall(game, ray->map.x, ray->map.y))
			ray->hit = 1;
	}
	if (ray->side == SIDE_Y)
		ray->perpwall_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->perpwall_dist = (ray->side_dist.y - ray->delta_dist.y);
}

void	init_line(t_line *line, t_game *game, t_ray *ray)
{
	line->height = (int)(game->mlx->height / ray->perpwall_dist);
	line->start = -1 * line->height / 2 + game->mlx->height / 2;
	if (line->start < 0)
		line->start = 0;
	line->end = line->height / 2 + game->mlx->height / 2 ;
	if (line->end >= game->mlx->height)
		line->end = game->mlx->height - 1;
}

void	set_texture_id(t_ray ray, t_player *player, int *id)
{
	(void)player;
	if (ray.side == SIDE_X && ray.dir.y >= 0)
		*id = 0;
	if (ray.side == SIDE_X && ray.dir.y < 0)
		*id = SOUTH_TEXTURE;
	if (ray.side == SIDE_Y && ray.dir.x >= 0)
		*id = WEST_TEXTURE;
	if (ray.side == SIDE_Y && ray.dir.x < 0)
		*id = EAST_TEXTURE;
}

void	set_texture_data(t_texture *texture, t_ray ray, t_game *game, t_line line)
{
	double	wall_x;

	if (ray.side == SIDE_Y)
		wall_x = game->player->square.y + ray.perpwall_dist * ray.dir.y;
	else
		wall_x = game->player->square.x + ray.perpwall_dist * ray.dir.x;
	wall_x -= floor(wall_x);
	texture->coord.x = (int)(wall_x * (double)64);
	if (ray.side == SIDE_Y && ray.dir.x < 0)
		texture->coord.x = 64 - texture->coord.x - 1;
	if (ray.side == SIDE_X && ray.dir.y > 0)
		texture->coord.x = 64 - texture->coord.x - 1;
	texture->step = 1.0 * 64 / line.height;
	texture->pos = (line.start - game->mlx->height / 2 + line.height / 2)
		* texture->step;
}

void	draw_texture(t_game *game, t_ray ray, t_line line, int x)
{
	t_texture	texture;
	t_img		img;
	int			tex_id;
	
	ft_memset(&texture, 0, sizeof(t_texture));
	set_texture_data(&texture, ray, game, line);
	set_texture_id(ray, game->player, &tex_id);
	img = game->texture[tex_id]->img;
	double y = line.start;
	while (y < line.end)
	{
		texture.coord.y = (int)texture.pos & (64 - 1);
		texture.pos += texture.step;

		if (x >= 0 && x < game->mlx->width
			&& y >= 0 && y < game->mlx->height)
		{
			game->mlx->img_3d->addr[((int)y * game->mlx->img_3d->line_length
				+ (int)(x * (game->mlx->img_3d->bits_per_pixel / 8)))]
				= img.addr[(((int)texture.coord.y * img.line_length) 
					+ ((int)texture.coord.x * img.bits_per_pixel / 8))];
		}

		if (x >= 0 && x < game->mlx->width
			&& y >= 0 && y < game->mlx->height)
		{
			game->mlx->img_3d->addr[((int)y * game->mlx->img_3d->line_length
				+ (int)(x * (game->mlx->img_3d->bits_per_pixel / 8))) + 1]
				= img.addr[(((int)texture.coord.y * img.line_length) 
					+ ((int)texture.coord.x * img.bits_per_pixel / 8)) + 1];
		}

		if (x >= 0 && x < game->mlx->width
			&& y >= 0 && y < game->mlx->height)
		{
			game->mlx->img_3d->addr[((int)y * game->mlx->img_3d->line_length
				+ (int)(x * (game->mlx->img_3d->bits_per_pixel / 8))) + 2]
				= img.addr[(((int)texture.coord.y * img.line_length) 
					+ ((int)texture.coord.x * img.bits_per_pixel / 8)) + 2];				
		}

		if (x >= 0 && x < game->mlx->width
			&& y >= 0 && y < game->mlx->height)
		{
			game->mlx->img_3d->addr[((int)y * game->mlx->img_3d->line_length
				+ (int)(x * (game->mlx->img_3d->bits_per_pixel / 8))) + 3]
				= img.addr[(((int)texture.coord.y * img.line_length) 
					+ ((int)texture.coord.x * img.bits_per_pixel / 8)) + 3];				
		}
		y++;
	}
}

void	ft_raycast(t_game *game, t_player *player)
{
	t_ray		ray;
	t_line		line;
	int		x;

	ft_memset(&ray, 0, sizeof(ray));
	ft_memset(&line, 0, sizeof(line));
	x = 0;
	ray.perpwall_dist = 0;
	while (x < game->mlx->width)
	{
		init_ray(game, &ray, player, x);
		init_dda_vector(&ray, player);
		run_dda(&ray, game);
		init_line(&line, game, &ray);
		draw_texture(game, ray, line, x);
		x++;
	}
}

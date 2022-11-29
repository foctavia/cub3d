/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:44 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/29 18:09:56 by owalsh           ###   ########.fr       */
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

int	is_wall_square(t_game *game, double square_x, double square_y)
{
	if ((int)square_y < 0 || (int)square_x < 0 || \
		(int)square_y >= game->map->height || (int)square_x >= game->map->width)
		return (FALSE);
	if (game->map->content[(int)square_y][(int)square_x] == WALL)
		return (TRUE);
	return (FALSE);
}

void	ft_raycast(t_game *game, t_player *player)
{
	t_ray	ray;
	t_coord	start;
	t_coord	end;

	
	double	time;
	double	old_time;

	int		hit;
	int		x;
	int		pitch;
	double	wall_x;
	t_coord	texture_coord;
	double	texture_step;
	double	texture_pos;
	t_img		img;
	int			width;
	int			height;

	img.img = mlx_xpm_file_to_image(game->mlx->mlx, "eagle.xpm", \
		&width, &height);
	img.addr = mlx_get_data_addr(img.img, \
		&img.bits_per_pixel, &img.line_length, &img.endian);


	time = 0;
	old_time = 0;
	x = 0;
	ray.perpwall_dist = 0;
	while (x < game->mlx->width )
	{
		hit = 0;
		ray.map.x = (int)player->square.x;
		ray.map.y = (int)player->square.y;
		ray.camera_x = 2 * x / (double)game->mlx->width - 1;
		ray.dir.x = player->dir.x + player->plane.x * ray.camera_x;
		ray.dir.y = player->dir.y + player->plane.y * ray.camera_x;
		
		ray.delta_dist.y = fabs(1 / ray.dir.y);
		ray.delta_dist.x = fabs(1 / ray.dir.x);
		
		hit = 0;
		
		if (ray.dir.x < 0)
		{
			ray.step.x = -1;
			ray.side_dist.x = (player->square.x - ray.map.x) * ray.delta_dist.x;
		}
		else
		{
			ray.step.x = 1;
			ray.side_dist.x = (ray.map.x + 1 - player->square.x) * ray.delta_dist.x;
		}
		if (ray.dir.y < 0)
		{
			ray.step.y = -1;
			ray.side_dist.y = (player->square.y - ray.map.y) * ray.delta_dist.y;
		}
		else
		{
			ray.step.y = 1;
			ray.side_dist.y = (ray.map.y  + 1 - player->square.y) * ray.delta_dist.y;
		}
		
		while (hit == 0)
		{
			if (ray.side_dist.x < ray.side_dist.y)
			{
				ray.side_dist.x += ray.delta_dist.x;
				ray.map.x += ray.step.x;
				ray.side = SIDE_X;
			}
			else
			{
				ray.side_dist.y += ray.delta_dist.y;
				ray.map.y += ray.step.y;
				ray.side = SIDE_Y;
			}
			if (is_wall_square(game, ray.map.x, ray.map.y))
			{
				hit = 1;
				bresenham(game, player->square, ray.map, HEX_RED);	
			}
		}
		if (ray.side == SIDE_X)
			ray.perpwall_dist = (ray.side_dist.x - ray.delta_dist.x);
		else
			ray.perpwall_dist = (ray.side_dist.y - ray.delta_dist.y);

		// pitch = 100;
		(void)pitch;
		
		ray.line_height = (int)(game->mlx->height / ray.perpwall_dist);
		start.x = x;
		end.x = x;
		
		start.y = -1 * ray.line_height / 2 + game->mlx->height / 2 ;
		if (start.y < 0)
			start.y = 0;
		end.y = ray.line_height / 2 + game->mlx->height / 2 ;
		if (end.y >= game->mlx->height)
			end.y = game->mlx->height - 1;
			
		if (ray.side == SIDE_X)
			wall_x = player->square.y + ray.perpwall_dist * ray.dir.y;
		else
			wall_x = player->square.x + ray.perpwall_dist * ray.dir.x;
		wall_x -= floor(wall_x);

		texture_coord.x = (int)(wall_x * (double)64);
		if (ray.side == SIDE_X && ray.dir.x > 0)
			texture_coord.x = 64 - texture_coord.x - 1;
		if (ray.side == SIDE_Y && ray.dir.y < 0)
			texture_coord.x = 64 - texture_coord.x - 1;

		texture_step = 1.0 * 64 / ray.line_height;
		texture_pos = (start.y - game->mlx->height / 2 + ray.line_height / 2) * texture_step;
		double y = start.y;
		while (y < end.y)
		{
			texture_coord.y = (int)texture_pos & (64 - 1);
			texture_pos += texture_step;


			if (start.x >= 0 && start.x < game->mlx->width
				&& y >= 0 && y < game->mlx->height)
			{
				game->mlx->img_3d->addr[((int)y * game->mlx->img_3d->line_length
					+ (int)(start.x * (game->mlx->img_3d->bits_per_pixel / 8)))]
					= img.addr[(((int)texture_coord.y * img.line_length) 
						+ ((int)texture_coord.x * img.bits_per_pixel / 8))];
				
			}

			if (start.x >= 0 && start.x < game->mlx->width
				&& y >= 0 && y < game->mlx->height)
			{
				game->mlx->img_3d->addr[((int)y * game->mlx->img_3d->line_length
					+ (int)(start.x * (game->mlx->img_3d->bits_per_pixel / 8))) + 1]
					= img.addr[(((int)texture_coord.y * img.line_length) 
						+ ((int)texture_coord.x * img.bits_per_pixel / 8)) + 1];
				
			}

			if (start.x >= 0 && start.x < game->mlx->width
				&& y >= 0 && y < game->mlx->height)
			{
				game->mlx->img_3d->addr[((int)y * game->mlx->img_3d->line_length
					+ (int)(start.x * (game->mlx->img_3d->bits_per_pixel / 8))) + 2]
					= img.addr[(((int)texture_coord.y * img.line_length) 
						+ ((int)texture_coord.x * img.bits_per_pixel / 8)) + 2];
				
			}

			if (start.x >= 0 && start.x < game->mlx->width
				&& y >= 0 && y < game->mlx->height)
			{
				game->mlx->img_3d->addr[((int)y * game->mlx->img_3d->line_length
					+ (int)(start.x * (game->mlx->img_3d->bits_per_pixel / 8))) + 3]
					= img.addr[(((int)texture_coord.y * img.line_length) 
						+ ((int)texture_coord.x * img.bits_per_pixel / 8)) + 3];
				
			}
			// if (start.x >= 0 && start.x < game->mlx->width
			// 	&& y >= 0 && y < game->mlx->height)
			// 	game->mlx->img_3d->addr[(int)y * game->mlx->img_3d->line_length
			// 		+ (int)(start.x * 4) + 1]
			// 		= img.addr[((int)texture_coord.y * 64) + ((int)texture_coord.x * 4) + 1];
			
			// if (start.x >= 0 && start.x < game->mlx->width
			// 	&& y >= 0 && y < game->mlx->height)
			// 	game->mlx->img_3d->addr[(int)y * game->mlx->img_3d->line_length
			// 		+ (int)(start.x * 4) + 2]
			// 		= img.addr[((int)texture_coord.y * 64) + ((int)texture_coord.x * 4) + 2];

			// if (start.x >= 0 && start.x < game->mlx->width
			// 	&& y >= 0 && y < game->mlx->height)
			// 	game->mlx->img_3d->addr[(int)y * game->mlx->img_3d->line_length
			// 		+ (int)(start.x * 4) + 3]
			// 		= img.addr[((int)texture_coord.y * 64) + ((int)texture_coord.x * 4) + 3];
			
			y++;
		}
		// bresenham_wall(game, start, end, HEX_RED);
		x++;

	}
	
}

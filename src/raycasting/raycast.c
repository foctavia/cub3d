/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:44 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/29 17:13:16 by owalsh           ###   ########.fr       */
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
	int	map_x;
	int	map_y;
	
	double	time;
	double	old_time;

	int		hit;
	int		x;


	time = 0;
	old_time = 0;
	x = 0;
	ray.perpwall_dist = 0;
	while (x < game->mlx->width )
	{
		hit = 0;
		map_x = (int)player->square.x;
		map_y = (int)player->square.y;
		printf("ray.map.x = %f\tray.map.y = %f\n", ray.map.x, ray.map.y);
		ray.camera_x = 2 * x / (double)game->mlx->width - 1;
		ray.dir.x = player->dir.x + player->plane.x * ray.camera_x;
		ray.dir.y = player->dir.y + player->plane.y * ray.camera_x;
		
		ray.delta_dist.y = fabs(1 / ray.dir.y);
		ray.delta_dist.x = fabs(1 / ray.dir.x);

		// printf("ray.delta_dist.x = %f\n", ray.delta_dist.x);
		// printf("ray.delta_dist.y = %f\n", ray.delta_dist.y);
		
		hit = 0;
		
		if (ray.dir.x < 0)
		{
			ray.step.x = -1;
			ray.side_dist.x = (player->square.x - (map_x)) * ray.delta_dist.x;
		}
		else
		{
			ray.step.x = 1;
			ray.side_dist.x = (map_x + 1 - player->square.x) * ray.delta_dist.x;
		}
		if (ray.dir.y < 0)
		{
			ray.step.y = -1;
			ray.side_dist.y = (player->square.y - map_y) * ray.delta_dist.y;
		}
		else
		{
			ray.step.y = 1;
			ray.side_dist.y = (map_y + 1 - player->square.y) * ray.delta_dist.y;
		}
		// printf("ray.side_dist.x = %f\n", ray.side_dist.x);
		// printf("ray.side_dist.y = %f\n", ray.side_dist.y);
		
		while (hit == 0)
		{
			if (ray.side_dist.x < ray.side_dist.y)
			{
				ray.side_dist.x += ray.delta_dist.x;
				map_x += ray.step.x;
				ray.side = SIDE_X;
			}
			else
			{
				ray.side_dist.y += ray.delta_dist.y;
				map_y += ray.step.y;
				ray.side = SIDE_Y;
			}
			if (is_wall_square(game, map_x, map_y))
			{
				hit = 1;
				t_coord	map;
				map.x = map_x;
				map.y = map_y;
				bresenham(game, player->square, map, HEX_RED);	
			}
		}
		if (ray.side == SIDE_X)
			ray.perpwall_dist = (ray.side_dist.x - ray.delta_dist.x);
		else
			ray.perpwall_dist = (ray.side_dist.y - ray.delta_dist.y);

	
		ray.line_height = (int)(game->mlx->height / ray.perpwall_dist) * 0.8;
		start.x = x;
		end.x = x;
		start.y = -1 * ray.line_height / 2 + game->mlx->height / 2;
		if (start.y < 0)
			start.y = 0;
		end.y = ray.line_height / 2 + game->mlx->height / 2;
		if (end.y >= game->mlx->height)
			end.y = game->mlx->height - 1;

		bresenham_wall(game, start, end, HEX_RED);
		x++;

	}
	
}

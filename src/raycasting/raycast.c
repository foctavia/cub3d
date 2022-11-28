/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:44 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/28 18:42:07 by owalsh           ###   ########.fr       */
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
	t_ray	ray;
	
	double	time;
	double	old_time;
	int		hit;

	int		x;
	int		draw_start;
	int		draw_end;

	time = 0;
	old_time = 0;
	
	x = 0;
	while (x < game->mlx->width )
	{

		ray.map.x = player->square.x;
		ray.map.y = player->square.y;
		ray.camera_x = 2 * x / (double)game->mlx->width - 1;
		ray.dir.x = player->dir.x + player->plane.x * ray.camera_x;
		ray.dir.y = player->dir.y + player->plane.y * ray.camera_x;

		ray.delta_dist.x = fabs(1 / ray.dir.x);
		ray.delta_dist.y = fabs(1 / ray.dir.y);

		hit = 0;
		
		if (ray.dir.x < 0)
		{
			ray.step.x = -1;
			ray.side_dist.x = (player->square.x - ray.map.x) * ray.delta_dist.x;
		}
		else
		{
			ray.step.x = 1;
			ray.side_dist.x = (ray.map.x + 1 - (player->square.x)) * ray.delta_dist.x;
		}
		if (ray.dir.y < 0)
		{
			ray.step.y = -1;
			ray.side_dist.y = (player->square.y - ray.map.y) * ray.delta_dist.y;
		}
		else
		{
			ray.step.y = 1;
			ray.side_dist.y = (ray.map.y + 1 - player->square.y) * ray.delta_dist.y;
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
			if (is_wall_hihi(game, ray.map.x, ray.map.y))
				hit = 1;
		}
		
		if (ray.side == SIDE_X)
			ray.perpwall_dist = (ray.side_dist.x - ray.delta_dist.x);
		else
			ray.perpwall_dist = (ray.side_dist.y - ray.delta_dist.y);
		
		ray.line_height = (int)(game->mlx->height / ray.perpwall_dist);
		
		draw_start = -1 * ray.line_height / 2 + game->mlx->height / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = ray.line_height / 2 + game->mlx->height / 2;
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

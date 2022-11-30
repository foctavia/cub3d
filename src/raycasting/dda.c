/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:34:08 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 19:16:25 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		ray->side_dist.x = (player->square.x - ray->map.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1 - player->square.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player->square.y - ray->map.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1 - player->square.y)
			* ray->delta_dist.y;
	}
}

void	run_dda(t_game *game, t_ray *ray)
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

void	init_line(t_game *game, t_line *line, t_ray *ray)
{
	line->height = (int)(game->mlx->height / ray->perpwall_dist);
	line->start = -1 * line->height / 2 + game->mlx->height / 2
		+ game->player->pitch;
	if (line->start < 0)
		line->start = 0;
	line->end = line->height / 2 + game->mlx->height / 2
		+ game->player->pitch;
	if (line->end >= game->mlx->height)
		line->end = game->mlx->height - 1;
}

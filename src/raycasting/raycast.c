/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:44 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/17 19:05:33 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_camera(t_game *game)
{
	game->camera = malloc(sizeof(t_camera));
	if (!game->camera)
		ft_error(ERR_MALLOC, 0, NULL, game);
	game->camera->width = 320;
	game->camera->height = 200;
	game->camera->fov = 60;
	game->camera->center.x = game->camera->width / 2;
	game->camera->center.y = game->camera->height / 2;
	game->camera->distance = game->camera->center.x / tan(30);
}

void	get_first_intersect(t_game *game, t_player *player, t_coord pos, t_coord *first, int i)
{
	if (player->dir == UP)
		first->y = floor(pos.y / game->mlx->elem_size) * game->mlx->elem_size - 1;
	else if (player->dir == DOWN) 
		first->y = floor(pos.y / game->mlx->elem_size) * game->mlx->elem_size + game->mlx->elem_size;
	first->x = pos.x + (pos.y - first->y) / tan(game->camera->fov) + i ;
}

t_coord	get_grid_coord(t_game *game, t_coord *pixel)
{
	t_coord	grid;

	grid.x = pixel->x * game->map->width / game->mlx->width;
	grid.y = pixel->y * game->map->height / game->mlx->height;
	return (grid);
}

void	get_intersect(t_coord *first, t_coord A, t_coord *intersect)
{
	intersect->x = first->x + A.x;
	intersect->y = first->y + A.y;	
}

void	bresenham_pixel(t_game *game, t_coord coord1, t_coord coord2, int color)
{
	float	d_x;
	float	d_y;
	int		max;

	d_x = coord2.x - coord1.x;
	d_y = coord2.y - coord1.y;
	max = BIGGER(ABS(d_x), ABS(d_y));
	d_x /= max;
	d_y /= max;
	while ((int)(coord1.x - coord2.x) || (int)(coord1.y - coord2.y))
	{
		put_pixel(game, game->mlx->minimap, coord1, color);
		coord1.x += d_x;
		coord1.y += d_y;
	}
}

void	draw_ray(t_game *game, t_player *player, int i)
{
	t_coord	intersect;
	t_coord	first;
	t_coord	A;

	get_first_intersect(game, player, player->pos, &first, i);
	if (is_wall(game, first.x, first.y))
	{
		bresenham_pixel(game, player->pos, first, HEX_BLUE);
		return ;
	}
	if (player->dir == UP)
		A.y = -1 * game->mlx->elem_size;
	else
		A.y = game->mlx->elem_size;
	A.x = game->mlx->elem_size / tan(game->camera->fov);
	get_intersect(&first, A, &intersect);
	while(!is_wall(game, intersect.x, intersect.y))
		get_intersect(&intersect, A, &intersect);
	bresenham_pixel(game, player->pos, intersect, HEX_YELLOW);
}

void	ft_raycast(t_game *game, t_mlx *mlx, t_player *player)
{
	int	i;

	(void)mlx;
	init_camera(game);
	i = 0;
	// while (i < game->camera->fov)
	// {
		draw_ray(game, player, i);
	// 	i += game->camera->fov / game->camera->width;
	// }
}

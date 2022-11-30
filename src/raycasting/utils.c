/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:44:35 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 18:11:24 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_in_range(t_game *game, int x, int y)
{
	if (x >= 0 && x < game->mlx->width
			&& y >= 0 && y < game->mlx->height)
		return (TRUE);
	return (FALSE);
}

int	is_pixel_in_window_range(t_game *game, t_coord coord)
{
	if (coord.x < 0 || coord.x > game->mlx->minimap->width)
		return (FALSE);
	if (coord.y < 0 || coord.y > game->mlx->minimap->height)
		return (FALSE);
	return (TRUE);
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

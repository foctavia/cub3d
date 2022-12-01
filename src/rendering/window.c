/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:13:29 by owalsh            #+#    #+#             */
/*   Updated: 2022/12/01 15:50:51 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_game *game)
{
	ft_clean(game);
	exit (EXIT_SUCCESS);
}

void	assign_mlx_size(t_game *game)
{
	int		width;
	int		height;

	mlx_get_screen_size(game->mlx->mlx, &width, &height);
	game->mlx->width = width * 0.8;
	game->mlx->height = height * 0.8;
}

void	assign_minimap_size(t_game *game, t_minimap *minimap)
{
	float	ratio;

	if (game->map->width > game->map->height)
	{
		minimap->width = game->mlx->width * 0.3;
		ratio = (float)game->map->height / game->map->width;
		minimap->height = ratio * minimap->width;
	}
	else
	{
		minimap->height = game->mlx->height * 0.3;
		ratio = (float)game->map->width / game->map->height;
		minimap->width = ratio * minimap->height;
	}
	if (game->map->height > game->map->width)
		minimap->elem_size = minimap->height / game->map->height;
	else
		minimap->elem_size = minimap->width / game->map->width;
}

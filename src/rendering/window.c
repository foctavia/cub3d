/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:13:29 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/24 16:22:49 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_game *game)
{
	if (game->mlx->img_minimap)
		mlx_destroy_image(game->mlx->mlx, game->mlx->img_minimap->img);
	if (game->mlx->img_3d)
		mlx_destroy_image(game->mlx->mlx, game->mlx->img_3d->img);
	if (game->mlx->texture)
		mlx_destroy_image(game->mlx->mlx, game->mlx->texture->img);
	if (game && game->mlx && game->mlx->mlx)
		mlx_loop_end(game->mlx->mlx);
	if (game && game->mlx && game->mlx->window)
		mlx_destroy_window(game->mlx->mlx, game->mlx->window);
	if (game && game->mlx && game->mlx->mlx)
	{
		mlx_destroy_display(game->mlx->mlx);
		free(game->mlx->mlx);
	}
	ft_clean(game);
	exit (EXIT_SUCCESS);
}

void	assign_mlx_size(t_game *game)
{
	game->mlx->width = WINDOW_W;
	game->mlx->height = WINDOW_H;
}

void	assign_minimap_size(t_game *game, t_minimap *minimap)
{
	float	ratio;

	if (game->map->width > game->map->height)
	{
		minimap->width = game->mlx->width * 0.5;
		ratio = (float)game->map->height / game->map->width;
		minimap->height = ratio * minimap->width;
	}
	else
	{
		minimap->height = game->mlx->height * 0.5;
		ratio = (float)game->map->width / game->map->height;
		minimap->width = ratio * minimap->height;
	}
	if (game->map->height > game->map->width)
		minimap->elem_size = minimap->height / game->map->height;
	else
		minimap->elem_size = minimap->width / game->map->width;
}

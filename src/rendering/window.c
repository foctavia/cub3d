/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:13:29 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/15 16:11:48 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_game *game)
{
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
	int		width;
	int		height;
	float	ratio;

	mlx_get_screen_size(game->mlx->mlx, &width, &height);
	if (game->map->width > game->map->height)
	{
		game->mlx->width = width * 0.8;
		ratio = (float)game->map->height / game->map->width;
		game->mlx->height = ratio * game->mlx->width;
	}
	else
	{
		game->mlx->height = height * 0.8;
		ratio = (float)game->map->width / game->map->height;
		game->mlx->width = ratio * game->mlx->height;
	}
	if (game->map->height > game->map->width)
		game->mlx->elem_size = game->mlx->height / game->map->height;
	else
		game->mlx->elem_size = game->mlx->width / game->map->width;
}

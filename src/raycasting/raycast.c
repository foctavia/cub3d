/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:44 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 20:53:35 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_raycast(t_game *game, t_player *player)
{
	t_line		line;
	t_ray		ray;
	int			x;

	ft_memset(&ray, 0, sizeof(ray));
	ft_memset(&line, 0, sizeof(line));
	x = 0;
	ray.perpwall_dist = 0;
	while (x < game->mlx->width)
	{
		init_ray(game, &ray, player, x);
		init_dda_vector(&ray, player);
		run_dda(game, &ray);
		init_line(game, &line, &ray);
		draw(game, ray, line, x);
		x++;
	}
}

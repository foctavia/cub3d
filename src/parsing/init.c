/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:36:29 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 10:34:27 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_map(t_game *game)
{
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		ft_error(ERR_MALLOC, 0, NULL, game);
	ft_memset(game->map, 0, sizeof(t_map));
	game->map->floor = malloc(sizeof(t_color));
	if (!game->map->floor)
		ft_error(ERR_MALLOC, 0, NULL, game);
	ft_memset(game->map->floor, 0, sizeof(t_color));
	game->map->ceiling = malloc(sizeof(t_color));
	if (!game->map->ceiling)
		ft_error(ERR_MALLOC, 0, NULL, game);
	ft_memset(game->map->ceiling, 0, sizeof(t_color));
	game->map->checker = malloc(sizeof(t_checker));
	if (!game->map->checker)
		ft_error(ERR_MALLOC, 0, NULL, game);
	ft_memset(game->map->checker, 0, sizeof(t_checker));
}

static void	init_mlx(t_game *game)
{
	game->mlx = malloc(sizeof(t_mlx));
	if (!game->mlx)
		ft_error(ERR_MALLOC, 0, NULL, game);
	ft_memset(game->mlx, 0, sizeof(t_mlx));
	game->mlx->minimap = malloc(sizeof(t_minimap));
	if (!game->mlx->minimap)
		ft_error(ERR_MALLOC, 0, NULL, game);
	ft_memset(game->mlx->minimap, 0, sizeof(t_minimap));
}

void	init_player(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		ft_error(ERR_MALLOC, 0, NULL, game);
	ft_memset(game->player, 0, sizeof(t_player));
}

void	init_texture(t_game *game)
{
	int	i;

	game->texture = malloc(sizeof(t_texture *) * 5);
	if (!game->texture)
		ft_error(ERR_MALLOC, 0, NULL, game);
	i = 0;
	while (i < 5)
	{
		game->texture[i] = malloc(sizeof(t_texture));
		if (!game->texture[i])
			ft_error(ERR_MALLOC, 0, NULL, game);
		ft_memset(game->texture[i], 0, sizeof(t_texture));
		i++;
	}
}

void	init_game(t_game *game, char *path)
{
	game->path = path;
	init_map(game);
	init_mlx(game);
	init_player(game);
	init_texture(game);
}

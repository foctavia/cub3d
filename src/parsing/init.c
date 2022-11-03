/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:36:29 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/03 16:21:29 by owalsh           ###   ########.fr       */
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
	game->map->texture = malloc(sizeof(t_texture));
	if (!game->map->texture)
		ft_error(ERR_MALLOC, 0, NULL, game);
	ft_memset(game->map->texture, 0, sizeof(t_texture));
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
}

static void	init_game(t_game *game, char *path)
{
	ft_memset(game, 0, sizeof(t_game));
	game->path = path;
	init_map(game);
	init_mlx(game);
}

static void	check_arg(t_game *game, char **argv)
{
	if (!argv || !argv[0] || !argv[1])
		exit(EXIT_FAILURE);
	if (file_extension(argv[1], ".cub"))
		ft_error(ERR_WRONG_FILE_EXTENSION, 0, argv[1], game);
	if (open_file(argv[1]) == -1)
		ft_error(ERR_MAP_PATH, 0, argv[1], game);
}

int	ft_parse_init(char **argv, t_game *game)
{
	check_arg(game, argv);
	init_game(game, argv[1]);
	if (ft_parse(game))
		exit(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

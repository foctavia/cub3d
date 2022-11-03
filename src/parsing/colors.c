/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:21:40 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/03 17:22:13 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_rgb(char *line, t_game *game, int *i, int color)
{
	int	j;
	int	rgb;

	j = *i;
	while (line && line[*i] && is_digit(line[*i]))
		(*i)++;
	if ((color == RED || color == GREEN)
		&& line[*i] == ',')
		line[*i] = '\0';
	else if (color == BLUE)
		line[*i] = '\0';
	else
		ft_error(ERR_MAP_INCOMPLETEID, 0, game->path, game);
	(*i)++;
	rgb = atoi(&line[j]);
	if (rgb < 0 || rgb > 255)
		ft_error(ERR_RGB, 0, game->path, game);
	return (rgb);
}

int	add_color(int id, char *line, int *i, t_game *game)
{
	(*i)++;
	while (line && line[*i] && is_space(line[*i]))
		(*i)++;
	if (!line[*i])
		ft_error(ERR_MAP_INCOMPLETEID, 0, game->path, game);
	if (id == FLOOR)
	{
		game->map->floor->red = set_rgb(line, game, i, RED);
		game->map->floor->green = set_rgb(line, game, i, GREEN);
		game->map->floor->blue = set_rgb(line, game, i, BLUE);
		game->map->checker->f = 1;
	}
	if (id == CEILING)
	{
		game->map->ceiling->red = set_rgb(line, game, i, RED);
		game->map->ceiling->green = set_rgb(line, game, i, GREEN);
		game->map->ceiling->blue = set_rgb(line, game, i, BLUE);
		game->map->checker->c = 1;
	}
	return (EXIT_SUCCESS);
}

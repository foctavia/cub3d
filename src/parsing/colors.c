/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:21:40 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 19:05:40 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	from_rgb_to_hex(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

static int	set_rgb(char *line, t_game *game, int *i, int color)
{
	int	j;
	int	rgb;

	while (line && line[*i] == ' ')
		(*i)++;
	j = *i;
	while (line && line[*i] && is_digit(line[*i]))
		(*i)++;
	if (color == RED || color == GREEN)
	{
		if (line[*i] == ',')
			line[*i] = '\0';
	}
	else if (color == BLUE)
		line[*i] = '\0';
	else
		ft_error_map(ERR_MAP_INCOMPLETEID, game->path, game);
	(*i)++;
	rgb = atoi(&line[j]);
	if (rgb < 0 || rgb > 255)
		ft_error_map(ERR_RGB, game->path, game);
	return (rgb);
}

int	add_color(int id, char *line, int *i, t_game *game)
{
	(*i)++;
	while (line && line[*i] && is_space(line[*i]))
		(*i)++;
	if (!line[*i])
		ft_error_map(ERR_MAP_INCOMPLETEID, game->path, game);
	if (id == FLOOR)
	{
		game->map->floor->red = set_rgb(line, game, i, RED);
		game->map->floor->green = set_rgb(line, game, i, GREEN);
		game->map->floor->blue = set_rgb(line, game, i, BLUE);
		game->map->floor->hex = from_rgb_to_hex(game->map->floor->red, \
			game->map->floor->green, game->map->floor->blue);
		game->map->checker->f = 1;
	}
	if (id == CEILING)
	{
		game->map->ceiling->red = set_rgb(line, game, i, RED);
		game->map->ceiling->green = set_rgb(line, game, i, GREEN);
		game->map->ceiling->blue = set_rgb(line, game, i, BLUE);
		game->map->ceiling->hex = from_rgb_to_hex(game->map->ceiling->red, \
			game->map->ceiling->green, game->map->ceiling->blue);
		game->map->checker->c = 1;
	}
	return (EXIT_SUCCESS);
}

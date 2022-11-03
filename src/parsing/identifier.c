/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:12:22 by foctavia          #+#    #+#             */
/*   Updated: 2022/11/03 09:27:48 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_identifier(char *str)
{
	if (str && !ft_strncmp("NO", str, 2))
		return (NORTH_TEXTURE);
	else if (str && !ft_strncmp("SO", str, 2))
		return (SOUTH_TEXTURE);
	else if (str && !ft_strncmp("WE", str, 2))
		return (WEST_TEXTURE);
	else if (str && !ft_strncmp("EA", str, 2))
		return (EAST_TEXTURE);
	else if (str && !ft_strncmp("F", str, 1))
		return (FLOOR);
	else if (str && !ft_strncmp("C", str, 1))
		return (CEILING);
	return (FALSE);
}

static void	assign_texture(t_game *game, int id, char *line, int n)
{
	if (id == NORTH_TEXTURE)
	{
		if (!game->map->texture->north)
			game->map->texture->north = ft_strndup(line, n);
		game->map->no++;
	}
	else if (id == SOUTH_TEXTURE)
	{
		if (!game->map->texture->south)
			game->map->texture->south = ft_strndup(line, n);
		game->map->so++;
	}
	else if (id == WEST_TEXTURE)
	{
		if (!game->map->texture->west)
			game->map->texture->west = ft_strndup(line, n);
		game->map->we++;
	}
	else if (id == EAST_TEXTURE)
	{
		if (!game->map->texture->east)
			game->map->texture->east = ft_strndup(line, n);
		game->map->ea++;
	}
}

int	add_texture(int id, char *line, int *i, t_game *game)
{
	int	j;

	*i += 2;
	while (line && line[*i] && is_space(line[*i]))
		(*i)++;
	if (!line[*i])
		ft_error(ERR_MAP_INCOMPLETEID, 0, game->path, game);
	j = *i;
	while (line && line[j] && !is_space(line[j]))
		j++;
	assign_texture(game, id, &line[*i], j - *i);
	*i = j;
	return (EXIT_SUCCESS);
}

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
		game->map->f = 1;
	}
	if (id == CEILING)
	{
		game->map->ceiling->red = set_rgb(line, game, i, RED);
		game->map->ceiling->green = set_rgb(line, game, i, GREEN);
		game->map->ceiling->blue = set_rgb(line, game, i, BLUE);
		game->map->c = 1;
	}
	return (EXIT_SUCCESS);
}

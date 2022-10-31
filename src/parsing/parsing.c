/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:35:59 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/31 16:36:48 by owalsh           ###   ########.fr       */
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

void	assign_texture(t_game *game, int id, char *line, int n)
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

int	set_rgb(char *line, t_game *game, int *i, int color)
{
	int	j;

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
	return (atoi(&line[j]));
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

int	complete_id(t_game *game)
{
	if (game && game->map && game->map->no == 1 && game->map->so == 1
		&& game->map->we == 1 && game->map->ea == 1
		&& game->map->f == 1 && game->map->c == 1)
		return (TRUE);
	else if (game && game->map && (game->map->no > 1 || game->map->so > 1
		|| game->map->we > 1 || game->map->ea > 1
		|| game->map->f > 1 || game->map->c > 1))
		ft_error(ERR_TOOMANY_ID, 0, game->path, game);
	return (FALSE);
}

int	check_allowed_char(char c, t_game *game)
{
	int		i;
	char	*allowed;

	i = 0;
	allowed = "10NWSO ";
	while (allowed && allowed[i])
	{
		if (allowed[i] == c)
			return (EXIT_SUCCESS);
		i++;
	}
	ft_error(ERR_FORBIDDEN_CHAR, 0, game->path, game);
	return (EXIT_FAILURE);
}

int	read_content(int fd, t_game *game)
{
	int		i;
	char	*line;
	int		heigth;
	int		length;

	line = get_next_line(fd);
	length = 0;
	heigth = 0;
	while (line)
	{
		i = 0;
		if (line[0] != '\n')
		{
			while (line[i] && is_space(line[i]))
				i++;
			if (line[i] != '1')
				ft_error(ERR_MAP_WALL, 0, game->path, game);
			while (line && line[i] && line[i] != '\n' && !check_allowed_char(line[i], game))
				i++;
			if (i > length)
				length = i;
		}
		heigth++;
		free(line);
		line = get_next_line(fd);
	}
	return (EXIT_SUCCESS);
}

void	check_endline(char *line, int i, t_game *game)
{
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] != '\n' && line[i] != '\0')
		ft_error(ERR_MAP_UNEXPECTED, 0, game->path, game);
}

int	ft_parse(t_game *game)
{
	char	*line;
	int		fd;
	int		i;
	int		id;

	fd = open(game->path, O_RDONLY);
	line = get_next_line(fd);
	while (line && !complete_id(game))
	{
		i = 0;
		if (line[0] != '\n')
		{
			while (line[i] && is_space(line[i]))
				i++;
			id = check_identifier(&line[i]);
			if (!id)
				ft_error(ERR_MAP_WRONGID, 0, game->path, game);
			if (id == FLOOR || id == CEILING)
				add_color(id, line, &i, game);
			else
				add_texture(id, line, &i, game);
			check_endline(line, i, game);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (complete_id(game))
		read_content(fd, game);
	close(fd);
	return (EXIT_SUCCESS);
}

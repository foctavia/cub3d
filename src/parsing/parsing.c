/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:35:59 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/28 18:24:19 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_file(char *path)
{
	int	fd;

	fd = open(path);
	if (fd == -1)
		ft_error(0, errno, path);
	return (fd);
}

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

int	add_texture(int id, char *line, char *path, t_game *game)
{
	int	i;

	i = 2;
	while (line && line[i] && is_space(line[i]))
		i++;
	if (!line[i])
		exit(ft_error(ERR_MAP_INCOMPLETEID, 0, path));
	if (id == NORTH_TEXTURE)
	{
		game->map->texture->north = &line[i];
		game->map->no = 1;
	}
	else if (id == SOUTH_TEXTURE)
	{
		game->map->texture->south = &line[i];
		game->map->so = 1;
	}
	else if (id == WEST_TEXTURE)
	{
		game->map->texture->west = &line[i];
		game->map->we = 1;
	}
	else if (id == EAST_TEXTURE)
	{
		game->map->texture->east = &line[i];
		game->map->ea = 1;
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	set_rgb(char *line, char *path, int *red, int *green, int *blue)
{
	int	i;

	i = 0;
	while (line && is_digit(line[i]))
		i++;
	if (line[i] == ',')
		line[i] = '\0';
	else
		exit(ft_error(ERR_MAP_INCOMPLETEID, 0, path));
	*red = atoi(line);
	line += i + 1;
	i = 0;
	while (line && is_digit(line[i]))
		i++;
	if (line[i] == ',')
		line[i] = '\0';
	else
		exit(ft_error(ERR_MAP_INCOMPLETEID, 0, path));
	*green = atoi(line);
	line += i + 1;
	i = 0;
	while (line && is_digit(line[i]))
		i++;
	line[i] = '\0';
	*blue = atoi(line);
	line += i + 1;
}


int	add_color(int id, char *line, char *path, t_game *game)
{
	int	i;
	int	red;
	int	green;
	int	blue;

	line++;
	while (line && is_space(&line[0]))
		line++;
	if (!line[0])
		exit(ft_error(ERR_MAP_INCOMPLETEID, 0, path));
	set_rgb(line, path, &red, &green, &blue);
	while (line && is_space(&line[0]))
	{
		if (!is_space(line[0]))
			exit(ft_error(ERR_MAP_WRONGID, 0, path));
		line++;
	}
	if (id == FLOOR)
	{
		game->map->floor->red = red;
		game->map->floor->green = green;
		game->map->floor->blue = blue;
		game->map->f = 1;
	}
	if (id == CEILING)
	{
		game->map->ceiling->red = red;
		game->map->ceiling->green = green;
		game->map->ceiling->blue = blue;
		game->map->c = 1;
	}
	return (EXIT_SUCCESS);
}

int	complete_id(t_game *game)
{
	if (game->map->no == 1 && game->map->no == 1
		&& game->map->no == 1 && game->map->no == 1
		&& game->map->no == 1 && game->map->no == 1)
		return (TRUE);
	return (FALSE);
}

int	parse_file(char *path, t_game *game)
{
	char	*line;
	int		fd;
	int		i;
	int		id;

	fd = open(path);
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
				exit(ft_error(ERR_MAP_WRONGID, 0, path));
			if (id == FLOOR || id == CEILING)
				add_color(id, &line[i], path, game);
			else
				add_texture(id, &line[i], path, game);
			while (line[i] && is_space(line[i]))
				i++;
			if (line[i])
				exit(ft_error(ERR_MAP_WRONGID, 0, path));
		}
		line = get_next_line(fd);
	}
	if (complete_id(game))
		read_content(fd, game, path);
	return (EXIT_SUCCESS);
}

int	ft_init(char **argv, t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	if (!argv || !argv[0] || !argv[1])
		exit(EXIT_FAILURE);
	if (open_file(argv[1]) == -1)
		exit(ft_error(ERR_MAP_PATH, 0, NULL));
	if (parse_file(argv[1], game))
		exit(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

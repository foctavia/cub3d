/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:14:33 by owalsh            #+#    #+#             */
/*   Updated: 2022/12/21 13:11:45 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	file_len(t_game *game)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(game->path, O_RDONLY);
	if (fd == -1)
		ft_error(0, errno, game->path, game);
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

void	copy_file(t_game *game)
{
	char	*line;
	int		fd;
	int		i;

	game->file = malloc(sizeof(char *) * (file_len(game) + 1));
	if (!game->file)
		ft_error(ERR_MALLOC, 0, NULL, game);
	game->file[0] = NULL;
	fd = open(game->path, __O_DIRECTORY);
	if (fd != -1)
		ft_error(0, errno, game->path, game);
	fd = open(game->path, O_RDONLY);
	if (fd == -1)
		ft_error(0, errno, game->path, game);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		game->file[i] = ft_strndup(line, ft_strlen(line));
		free(line);
		line = get_next_line(fd);
		i++;
	}
	game->file[i] = NULL;
	close(fd);
}

char	*copy_line(char *line, t_game *game)
{
	char	*copy;
	int		i;

	copy = malloc(sizeof(char) * (game->map->width + 1));
	if (!copy)
	{
		ft_error(ERR_MALLOC, 0, NULL, game);
		return (NULL);
	}
	i = 0;
	while (line && line[i] && line[i] != '\n')
	{
		copy[i] = line[i];
		i++;
	}
	while (i < game->map->width)
	{
		copy[i] = ' ';
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

void	copy_map(t_game *game, char **file, int *line_index)
{
	int	i;

	i = 0;
	game->map->content = malloc(sizeof(char *) * (game->map->height + 1));
	if (!game->map->content)
		ft_error(ERR_MALLOC, 0, NULL, game);
	while (i < game->map->height && file && file[(*line_index) + i])
	{
		game->map->content[i] = copy_line(file[(*line_index) + i], game);
		i++;
	}
	game->map->content[i] = NULL;
	*line_index += i;
}

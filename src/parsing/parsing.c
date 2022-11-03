/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:35:59 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/03 17:16:54 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_endline(char *line, int i, t_game *game)
{
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] != '\n' && line[i] != '\0')
		ft_error(ERR_MAP_UNEXPECTED, 0, game->path, game);
}

void	copy_file(t_game *game, char **tab)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(game->path, O_RDONLY);
	if (fd == -1)
		ft_error(ERR_MAP_PATH, 0, game->map, game);
	line = get_next_line(fd);
	while (line)
	{
		i++;
		line = get_next_line(fd);
	}
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		ft_error(ERR_MALLOC, 0, NULL, game);
	close(fd);
	fd = open(game->path, O_RDONLY);
	if (fd == -1)
		ft_error(ERR_MAP_PATH, 0, game->map, game);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		tab[i] = ft_strndup(line, ft_strlen(line));
		line = get_next_line(fd);
		i++;
	}
	tab[i] = NULL;
}

int	ft_parse(t_game *game)
{
	char	**tab;
	int		line;

	copy_file(game, tab);
	get_identifiers(game, tab, &line);
	check_map(game, tab, &line);
	copy_map(game, tab, &line);
	return (EXIT_SUCCESS);
}

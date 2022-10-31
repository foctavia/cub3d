/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:35:59 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/31 19:04:21 by foctavia         ###   ########.fr       */
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
	{
		get_map_content(fd, game);
		check_map_content(game, game->map->content);
	}
	close(fd);
	display_map(game->map);
	return (EXIT_SUCCESS);
}

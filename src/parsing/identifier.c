/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:12:22 by foctavia          #+#    #+#             */
/*   Updated: 2022/12/21 17:21:54 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_identifier(t_game *game, char *str)
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
	else if (str && !ft_strncmp("1", str, 1))
		return (MAP_START);
	return (ft_error_map(ERR_MAP_WRONGID, game->path, game));
}

int	complete_identifiers(t_game *game)
{
	t_checker	*checker;

	checker = game->map->checker;
	if (checker->c == 1 && checker->f == 1 && checker->no == 1
		&& checker->so == 1 && checker->we == 1 && checker->ea == 1)
		return (TRUE);
	else if (checker->c > 1 && checker->f > 1 && checker->no > 1
		&& checker->so > 1 && checker->we > 1 && checker->ea > 1)
		ft_error_map(ERR_TOOMANY_ID, game->path, game);
	return (FALSE);
}

void	goto_map_content(t_game *game, char **file, int *j)
{
	int	i;

	if (!complete_identifiers(game))
		ft_error_map(ERR_MAP_INCOMPLETEID, game->path, game);
	while (file && file[*j])
	{
		i = 0;
		while (file[*j][i] && is_space(file[*j][i]))
			i++;
		if (file[*j][i])
			break ;
		(*j)++;
	}
}

static void	check_endline(char *line, int i, t_game *game)
{
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] != '\n' && line[i] != '\0')
		ft_error_map(ERR_MAP_UNEXPECTED, game->path, game);
}

void	get_identifiers(t_game *game, char **file, int *line_index)
{
	int	i;
	int	j;
	int	id;

	j = 0;
	while (!complete_identifiers(game) && file && file[j])
	{
		i = 0;
		while (file[j][i] && is_space(file[j][i]))
			i++;
		if (file[j][i])
		{
			id = check_identifier(game, &file[j][i]);
			if (id == MAP_START)
				break ;
			else if (id == FLOOR || id == CEILING)
				add_color(id, file[j], &i, game);
			else
				add_texture(id, file[j], &i, game);
			check_endline(file[j], i, game);
		}
		j++;
	}
	goto_map_content(game, file, &j);
	*line_index += j;
}

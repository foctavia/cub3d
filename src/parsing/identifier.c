/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:12:22 by foctavia          #+#    #+#             */
/*   Updated: 2022/11/03 19:00:07 by owalsh           ###   ########.fr       */
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

int	complete_identifiers(t_game *game)
{
	t_checker	*checker;

	checker = game->map->checker;
	if (checker->c == 1 && checker->f == 1 && checker->no == 1
		&& checker->so == 1 && checker->we == 1 && checker->ea == 1)
		return (TRUE);
	else if (checker->c > 1 && checker->f > 1 && checker->no > 1
		&& checker->so > 1 && checker->we > 1 && checker->ea > 1)
		ft_error(ERR_TOOMANY_ID, 0, game->path, game);
	return (FALSE);		
}

void	goto_map_content(char **tab, int *j)
{
	int	i;

	while (tab && tab[*j])
	{
		i = 0;
		while (tab[*j][i] && is_space(tab[*j][i]))
			i++;
		if (tab[*j][i])
			break;
		(*j)++;
	}
}

void	get_identifiers(t_game *game, char **tab, int *line)
{
	int	i;
	int	j;
	int	id;

	j = 0;
	while (!complete_identifiers(game) && tab && tab[j])
	{
		i = 0;
		while (tab[j][i] && is_space(tab[j][i]))
			i++;
		if (tab[j][i])
		{
			id = check_identifier(&tab[j][i]);
			if (!id)
				ft_error(ERR_MAP_WRONGID, 0, game->path, game);
			else if (id == FLOOR || id == CEILING)
				add_color(id, &tab[j][i], &i, game);
			else
				add_texture(id, &tab[j][i], &i, game);
			check_endline(&tab[j][i], i, game);
		}
		j++;
	}
	goto_map_content(tab, &j);
	*line += j;
}

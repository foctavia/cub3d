/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:19:06 by foctavia          #+#    #+#             */
/*   Updated: 2022/11/18 16:03:33 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_allowed_char(char c, t_game *game)
{
	int		i;
	char	*allowed;

	i = 0;
	allowed = "102NWSE ";
	while (allowed && allowed[i])
	{
		if (allowed[i] == c)
			return (EXIT_SUCCESS);
		i++;
	}
	ft_error_map(ERR_FORBIDDEN_CHAR, game->path, game);
	return (EXIT_FAILURE);
}

void	parse_map(t_game *game, char **file, int *line_index)
{
	int	i;
	int	j;

	i = *line_index;
	while (file && file[i])
	{
		j = 0;
		if (file[i][0] != '\n')
		{
			while (file[i][j] && is_space(file[i][j]))
				j++;
			while (file && file[i][j] && file[i][j] != '\n' \
				&& !check_allowed_char(file[i][j], game))
				j++;
			if (j > game->map->width)
				game->map->width = j;
		}
		else
			break ;
		game->map->height++;
		i++;
	}
}

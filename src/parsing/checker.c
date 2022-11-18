/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:19:21 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/18 16:02:34 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char c)
{
	int		i;
	char	*player;

	i = 0;
	player = "NSWE";
	while (player && player[i])
	{
		if (player[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static void	check_player(t_game *game, char **content)
{
	int	i;
	int	j;
	int	player;

	player = 0;
	i = 0;
	while (content && content[i])
	{
		j = 0;
		while (content[i] && content[i][j])
		{
			if (is_player(content[i][j]))
				player++;
			j++;
		}
		i++;
	}
	if (player != 1)
		ft_error_map(ERR_MAP_PLAYER, game->path, game);
}

static void	check_end_map(t_game *game, int line_index)
{
	int	i;
	int	j;

	i = line_index;
	while (game->file && game->file[i])
	{
		j = 0;
		while (game->file[i] && game->file[i][j])
		{
			if (!is_space(game->file[i][j]))
				ft_error_map(ERR_MAP_UNEXPECTED, game->path, game);
			j++;
		}
		i++;
	}
}

void	checker_map(t_game *game, int line_index)
{
	check_walls(game, game->map->content);
	check_player(game, game->map->content);
	check_end_map(game, line_index);
}

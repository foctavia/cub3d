/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:27:30 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/09 17:53:56 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_top_bottom(t_game *game, char *content)
{
	int	j;

	j = 0;
	while (content && content[j])
	{
		if (content[j] != '1' && content[j] != ' ')
			ft_error_map(ERR_MAP_WALL, game->path, game);
		j++;
	}
}

static void	check_sides(t_game *game, char **content, int i, int j)
{
	int	top;
	int	bottom;
	int	left;
	int	right;

	top = i - 1;
	bottom = i + 1;
	left = j - 1;
	right = j + 1;
	if ((content[i][j] == '0')
		&& ((content[i][right] == ' ') || (j && content[i][left] == ' '))
		&& ((top >= 0 && content[top][j] != ' ')
		&& ((bottom <= game->map->width) && content[bottom][j] != ' ')))
		ft_error_map(ERR_MAP_WALL, game->path, game);
	else if ((content[i][j] == '0')
		&& (top >= 0 && content[top][j] == ' ')
		&& ((bottom <= game->map->width) && content[bottom][j] != ' '))
		ft_error_map(ERR_MAP_WALL, game->path, game);
	else if ((content[i][j] == '0')
		&& ((bottom <= game->map->width) && content[bottom][j] == ' ')
		&& (top >= 0 && content[top][j] != ' '))
		ft_error_map(ERR_MAP_WALL, game->path, game);
}

static void	check_player_position(t_game *game, char **content, int i, int j)
{
	int		top;
	int		bottom;
	int		left;
	int		right;
	char	*player;

	top = i - 1;
	bottom = i + 1;
	left = j - 1;
	right = j + 1;
	player = "NSWE";
	if (is_player(content[i][j])
		&& ((content[i][right] == ' ') || (j && content[i][left] == ' ')))
		ft_error_map(ERR_MAP_WALL, game->path, game);
	else if (is_player(content[i][j])
		&& (top >= 0 && content[top][j] == ' '))
		ft_error_map(ERR_MAP_WALL, game->path, game);
	else if (is_player(content[i][j])
		&& ((bottom <= game->map->width) && content[bottom][j] == ' '))
		ft_error_map(ERR_MAP_WALL, game->path, game);
}

void	check_walls(t_game *game, char **content)
{
	int		i;
	int		j;

	i = 0;
	while (content && content[i])
	{
		if (i == 0 || i == game->map->height - 1)
			check_top_bottom(game, content[i]);
		else
		{
			j = 0;
			while (content[i] && content[i][j] && is_space(content[i][j]))
				j++;
			if (content[i][j] != '1')
				ft_error_map(ERR_MAP_WALL, game->path, game);
			while (content[i] && content[i][j])
			{
				check_sides(game, content, i, j);
				check_player_position(game, content, i, j);
				j++;
			}
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:17:38 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 18:00:03 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	valid_texture_file(t_game *game)
{
	t_texture	**texture;

	texture = game->texture;
	if (texture[0] && texture[0]->path
		&& open_file(texture[0]->path) == -1)
		ft_error(0, errno, texture[0]->path, game);
	else if (texture[1] && texture[1]->path
		&& open_file(texture[1]->path) == -1)
		ft_error(0, errno, texture[1]->path, game);
	else if (texture[2] && texture[2]->path
		&& open_file(texture[2]->path) == -1)
		ft_error(0, errno, texture[2]->path, game);
	else if (texture[3] && texture[3]->path
		&& open_file(texture[3]->path) == -1)
		ft_error(0, errno, texture[3]->path, game);
	else if (texture[4] && texture[4]->path
		&& open_file(texture[4]->path) == -1)
		ft_error(0, errno, texture[4]->path, game);
}

static void	assign_texture(t_game *game, int id, char *line, int n)
{
	if (!game->texture)
		return ;
	if (id == NORTH_TEXTURE)
	{
		game->texture[0]->path = ft_strndup(line, n);
		game->map->checker->no++;
	}
	else if (id == SOUTH_TEXTURE)
	{
		game->texture[1]->path = ft_strndup(line, n);
		game->map->checker->so++;
	}
	else if (id == WEST_TEXTURE)
	{
		game->texture[2]->path = ft_strndup(line, n);
		game->map->checker->we++;
	}
	else if (id == EAST_TEXTURE)
	{
		game->texture[3]->path = ft_strndup(line, n);
		game->map->checker->ea++;
	}
	else if (id == SPRITE_TEXTURE)
	{
		game->texture[4]->path = ft_strndup(line, n);
		game->map->checker->sp++;
	}
}

int	add_texture(int id, char *line, int *i, t_game *game)
{
	int	j;

	*i += 2;
	while (line && line[*i] && is_space(line[*i]))
		(*i)++;
	if (!line[*i])
		ft_error_map(ERR_MAP_INCOMPLETEID, game->path, game);
	j = *i;
	while (line && line[j] && !is_space(line[j]))
		j++;
	assign_texture(game, id, &line[*i], j - *i);
	valid_texture_file(game);
	*i = j;
	return (EXIT_SUCCESS);
}

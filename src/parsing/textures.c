/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:17:38 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/29 19:00:33 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	valid_texture_file(t_game *game)
// {
// 	t_texture	*texture;

// 	texture = game->map->texture;
// 	if (texture->north && open_file(texture->north) == -1)
// 		ft_error(0, errno, texture->north, game);
// 	else if (texture->south && open_file(texture->south) == -1)
// 		ft_error(0, errno, texture->south, game);
// 	else if (texture->west && open_file(texture->west) == -1)
// 		ft_error(0, errno, texture->west, game);
// 	else if (texture->east && open_file(texture->east) == -1)
// 		ft_error(0, errno, texture->east, game);
// }

static void	assign_texture(t_game *game, int id, char *line, int n)
{
	if (!game->texture)
		return ; 
	if (id == NORTH_TEXTURE)
	{
		game->texture[0].id = id;
		game->texture[0].path = ft_strndup(line, n);
		game->map->checker->no++;
	}
	else if (id == SOUTH_TEXTURE)
	{
		game->texture[1].id = id;
		game->texture[1].path = ft_strndup(line, n);
		game->map->checker->so++;
	}
	else if (id == WEST_TEXTURE)
	{
		game->texture[2].id = id;
		game->texture[2].path = ft_strndup(line, n);
		game->map->checker->we++;
	}
	else if (id == EAST_TEXTURE)
	{
		game->texture[3].id = id;
		game->texture[3].path = ft_strndup(line, n);
		game->map->checker->ea++;
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
	// valid_texture_file(game);
	*i = j;
	return (EXIT_SUCCESS);
}

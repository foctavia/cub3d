/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:31:33 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/10 15:29:45 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		if (tab[i])
			free(tab[i++]);
	}
	free(tab);
}

void	free_map(t_map *map)
{
	if (map)
	{
		if (map->floor)
			free(map->floor);
		if (map->ceiling)
			free(map->ceiling);
		if (map->texture)
		{
			if (map->texture->south)
				free(map->texture->south);
			if (map->texture->north)
				free(map->texture->north);
			if (map->texture->west)
				free(map->texture->west);
			if (map->texture->east)
				free(map->texture->east);
			free(map->texture);
		}
		if (map->content)
			free_tab(map->content);
		if (map->checker)
			free(map->checker);
		free(map);
	}
}

void	ft_clean(t_game *game)
{
	if (game)
	{
		if (game->map)
			free_map(game->map);
		if (game->mlx)
			free(game->mlx);
		if (game->file)
			free_tab(game->file);
	}
}

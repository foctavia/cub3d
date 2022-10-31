/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:31:33 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/31 15:38:15 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

void	ft_clean(t_game *game)
{
	if (game)
	{
		if (game->map)
		{
			if (game->map->floor)
				free(game->map->floor);
			if (game->map->ceiling)
				free(game->map->ceiling);
			if (game->map->texture)
			{
				if (game->map->texture->south)
					free(game->map->texture->south);
				if (game->map->texture->north)
					free(game->map->texture->north);
				if (game->map->texture->west)
					free(game->map->texture->west);
				if (game->map->texture->east)
					free(game->map->texture->east);
				free(game->map->texture);
			}
			if (game->map->content)
				free_tab(game->map->content);
			free(game->map);
		}
		if (game->mlx)
			free(game->mlx);
	}
}

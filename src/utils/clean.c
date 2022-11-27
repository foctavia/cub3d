/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:31:33 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/27 18:35:54 by owalsh           ###   ########.fr       */
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

void	free_buffer(t_game *game)
{
	int	y;
	y = 0;
	while (y < game->mlx->height)
	{
		free(game->mlx->buffer[y]);
		y++;
	}
	free(game->mlx->buffer);
}

void	ft_clean(t_game *game)
{
	if (game)
	{
		if (game->map)
			free_map(game->map);
		if (game->mlx)
		{
			if (game->mlx->buffer)
				free_buffer(game);
			if (game->mlx->minimap)
				free(game->mlx->minimap);
			free(game->mlx);
		}
		if (game->camera)
			free(game->camera);
		if (game->file)
			free_tab(game->file);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:31:33 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/31 18:43:09 by foctavia         ###   ########.fr       */
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

void	free_content(t_content **content)
{
	t_content	*tmp;
	t_content	*next;

	if (*content)
	{
		tmp = *content;
		while (tmp)
		{
			next = tmp->next;
			if (tmp->line)
				free(tmp->line);
			free(tmp);
			tmp = next;
		}
	}
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
			free_content(&map->content);
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
	}
}

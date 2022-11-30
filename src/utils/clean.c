/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:31:33 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 19:01:34 by owalsh           ###   ########.fr       */
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
		if (map->content)
			free_tab(map->content);
		if (map->checker)
			free(map->checker);
		free(map);
	}
}

void	free_texture(t_game *game, t_texture **texture)
{
	int	i;

	(void)game;
	i = 0;
	while (i < 4)
	{
		if (texture[i])
		{
			if (texture[i]->path)
				free(texture[i]->path);
			free(texture[i]);
		}
		i++;
	}
	free(texture);
}

void	destroy_mlx(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->texture[i] && &game->texture[i]->img)
			mlx_destroy_image(game->mlx->mlx, game->texture[i]->img.img);
		i++;
	}
	if (&game->mlx->img_minimap)
		mlx_destroy_image(game->mlx->mlx, game->mlx->img_minimap.img);
	if (&game->mlx->img_3d)
		mlx_destroy_image(game->mlx->mlx, game->mlx->img_3d.img);
	if (game->mlx->mlx)
		mlx_loop_end(game->mlx->mlx);
	if (game->mlx->window)
		mlx_destroy_window(game->mlx->mlx, game->mlx->window);
	if (game->mlx->mlx)
	{
		mlx_destroy_display(game->mlx->mlx);
		free(game->mlx->mlx);
	}
}

void	ft_clean(t_game *game)
{
	if (game)
	{
		if (game->map)
			free_map(game->map);
		if (game->mlx)
		{
			if (game->mlx->mlx)
				destroy_mlx(game);
			if (game->texture)
				free_texture(game, game->texture);
			if (game->mlx->minimap)
				free(game->mlx->minimap);
			free(game->mlx);
		}
		if (game->file)
			free_tab(game->file);
	}
}

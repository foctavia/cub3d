/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:52:47 by foctavia          #+#    #+#             */
/*   Updated: 2022/11/29 18:42:04 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_player(t_game *game)
{
	printf("game->player: %p\n", game->player);
	// if (game->player->dir == UP)
	// 	printf("player->dir == UP\n");
	// else if (game->player->dir == DOWN)
	// 	printf("player->dir == DOWN\n");
	// else if (game->player->dir == LEFT)
	// 	printf("player->dir == LEFT\n");
	// else if (game->player->dir == RIGHT)
	// 	printf("player->dir == RIGHT\n");
	// else
	// 	printf("player->dir = %f\n", game->player->dir);
}

void	display_map(t_map *map)
{
	int i;

	printf("====================MAP====================\n\n");
	if (map)
	{
		// if (map->texture)
		// {
		// 	if (map->texture->north)
		// 		printf("NO : |%s|\n", map->texture->north);
		// 	if (map->texture->south)
		// 		printf("SO : |%s|\n", map->texture->south);
		// 	if (map->texture->north)
		// 		printf("WE : |%s|\n", map->texture->west);
		// 	if (map->texture->north)
		// 		printf("EA : |%s|\n", map->texture->east);
		// 	printf("\n");
		// }
		if (map->floor)
			printf("F : %d,%d,%d\n", map->floor->red, map->floor->green, map->floor->blue);
		if (map->ceiling)
			printf("C : %d,%d,%d\n", map->ceiling->red, map->ceiling->green, map->floor->blue);
		printf("\nwidth : %d\nheight : %d\n\n", map->width, map->height);
		i = 0;
		if (map->content)
			printf("map content:\n");
		while (map->content && map->content[i])
		{
			printf("|%s|\n", map->content[i]);
			i++;
		}
	}
	else
		printf("no map\n");
}

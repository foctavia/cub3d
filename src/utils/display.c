/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:52:47 by foctavia          #+#    #+#             */
/*   Updated: 2022/11/03 15:26:24 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_map(t_map *map)
{
	printf("====================MAP====================\n\n");
	if (map)
	{
		t_content	*tmp;
		
		if (map->texture)
		{
			if (map->texture->north)
				printf("NO : %s\n", map->texture->north);
			if (map->texture->south)
				printf("SO : %s\n", map->texture->south);
			if (map->texture->north)
				printf("WE : %s\n", map->texture->west);
			if (map->texture->north)
				printf("EA : %s\n", map->texture->east);
			printf("\n");
		}
		if (map->floor)
			printf("F : %d,%d,%d\n", map->floor->red, map->floor->green, map->floor->blue);
		if (map->ceiling)
			printf("C : %d,%d,%d\n", map->ceiling->red, map->ceiling->green, map->floor->blue);
		printf("\nwidth : %d\nheight : %d\n\n", map->width, map->height);
		if (map->content)
		{
			tmp = map->content;
			while (tmp)
			{
				if (tmp->line)
					printf("|%s|\n", tmp->line);
				tmp = tmp->next;
			}
		}
	}
	else
		printf("no map\n");
}

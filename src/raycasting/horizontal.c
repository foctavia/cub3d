/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:58:06 by foctavia          #+#    #+#             */
/*   Updated: 2022/11/18 17:25:27 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_first_x_intersect(t_game *game, t_player *player, t_coord pos, t_coord *first, float i)
{
	float	player_tan;

	(void)i;
	player_tan = -1 / tan(player->dir);
	if (player->dir < LEFT && player->dir > RIGHT_MIN)
		first->y = floor(pos.y / game->mlx->elem_size) * game->mlx->elem_size - 0.0001;
	else if (player->dir > LEFT && player->dir < RIGHT_MAX)
		first->y = floor(pos.y / game->mlx->elem_size) * game->mlx->elem_size + game->mlx->elem_size;
	first->x = (pos.y - first->y) * player_tan + pos.x;
}

void	get_x_intersect(t_coord *first, t_coord A, t_coord *intersect)
{
	intersect->x = first->x + A.x;
	intersect->y = first->y + A.y;	
}

t_coord	get_horizontal_ray(t_game *game, t_player *player, float i)
{
	t_coord	intersect;
	t_coord	first;
	t_coord	A;
	float	player_tan;

	player_tan = -1 / tan(player->dir);
	if (player->dir == RIGHT || player->dir == LEFT)
		return (player->pos);
	get_first_x_intersect(game, player, player->pos, &first, i);
	if (is_wall(game, first.x, first.y) && get_grid_coord(game, intersect.x, 'x') <= game->map->width)
		return (first);
	if (player->dir < LEFT && player->dir > RIGHT_MIN)
		A.y = -1 * game->mlx->elem_size;
	else if (player->dir > LEFT && player->dir < RIGHT_MAX)
		A.y = game->mlx->elem_size;
	A.x = -1 * A.y * player_tan;
	get_x_intersect(&first, A, &intersect);
	while(!is_wall(game, intersect.x, intersect.y) && get_grid_coord(game, intersect.x, 'x') <= game->map->width)
		get_x_intersect(&intersect, A, &intersect);
	return (intersect);
}

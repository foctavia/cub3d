/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:58:13 by foctavia          #+#    #+#             */
/*   Updated: 2022/11/21 13:57:35 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_first_y_intersect(t_game *game, t_coord pos, \
	t_coord *first, float ray_dir)
{
	float	player_tan;

	player_tan = -1 * (tan(ray_dir));
	if (is_looking_right(ray_dir))
		first->x = (floor(pos.x / game->mlx->elem_size) + 1) * \
			game->mlx->elem_size;
	else if (is_looking_left(ray_dir))
		first->x = (floor(pos.x / game->mlx->elem_size) - 0.0001) * \
			game->mlx->elem_size;
	first->y = (pos.x - first->x) * player_tan + pos.y;
}

void	get_y_intersect(t_coord *first, t_coord range, t_coord *intersect)
{
	intersect->x = first->x + range.x;
	intersect->y = first->y + range.y;
}

t_coord	get_vertical_ray(t_game *game, t_player *player, float ray_dir)
{
	t_coord	intersect;
	t_coord	first;
	t_coord	range;
	float	player_tan;

	player_tan = -1 * (tan(ray_dir));
	if (ray_dir == UP || ray_dir == DOWN)
		return (player->pos);
	get_first_y_intersect(game, player->pos, &first, ray_dir);
	if (is_wall(game, first.x, first.y) && \
		get_grid_coord(game, intersect.y, 'y') <= game->map->height)
		return (first);
	if (is_looking_left(ray_dir))
		range.x = -1 * game->mlx->elem_size;
	else if (is_looking_right(ray_dir))
		range.x = game->mlx->elem_size;
	range.y = -1 * range.x * player_tan;
	get_y_intersect(&first, range, &intersect);
	while (!is_wall(game, intersect.x, intersect.y) && \
		get_grid_coord(game, intersect.y, 'y') <= game->map->height)
		get_y_intersect(&intersect, range, &intersect);
	return (intersect);
}

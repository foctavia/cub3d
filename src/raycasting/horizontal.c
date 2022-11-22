/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:58:06 by foctavia          #+#    #+#             */
/*   Updated: 2022/11/21 15:15:02 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_first_x_intersect(t_game *game, t_coord pos, \
	t_coord *first, float ray_dir)
{
	float	player_tan;

	player_tan = -1 / tan(ray_dir);
	if (is_looking_down(ray_dir))
		first->y = (floor(pos.y / game->mlx->minimap->elem_size) + 1) * \
			game->mlx->minimap->elem_size;
	else if (is_looking_up(ray_dir))
		first->y = (floor(pos.y / game->mlx->minimap->elem_size) - 0.0001) * \
			game->mlx->minimap->elem_size;
	first->x = (pos.y - first->y) * player_tan + pos.x;
}

void	get_x_intersect(t_coord *first, t_coord range, t_coord *intersect)
{
	intersect->x = first->x + range.x;
	intersect->y = first->y + range.y;
}

t_coord	get_horizontal_ray(t_game *game, t_player *player, float ray_dir)
{
	t_coord	intersect;
	t_coord	first;
	t_coord	range;
	float	player_tan;

	player_tan = -1 / tan(ray_dir);
	if (ray_dir == RIGHT || ray_dir == LEFT)
		return (player->pos);
	get_first_x_intersect(game, player->pos, &first, ray_dir);
	if (is_wall(game, first.x, first.y) == 1 && \
		get_grid_coord(game, intersect.x, 'x') <= game->map->width)
		return (first);
	if (is_looking_up(ray_dir))
		range.y = -1 * game->mlx->minimap->elem_size;
	else if (is_looking_down(ray_dir))
		range.y = game->mlx->minimap->elem_size;
	range.x = -1 * range.y * player_tan;
	get_x_intersect(&first, range, &intersect);
	while (!is_wall(game, intersect.x, intersect.y)
		&& get_grid_coord(game, intersect.x, 'x') <= game->map->width)
		get_x_intersect(&intersect, range, &intersect);
	return (intersect);
}

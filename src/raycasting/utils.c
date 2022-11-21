/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:44:35 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/21 15:21:42 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_pixel_in_window_range(t_game *game, t_coord coord)
{
	if (coord.x < 0 || coord.x > game->mlx->minimap->width)
		return (FALSE);
	if (coord.y < 0 || coord.y > game->mlx->minimap->height)
		return (FALSE);
	return (TRUE);
}

int	is_looking_up(float angle)
{
	if (angle > LEFT && angle < RIGHT_MAX)
		return (TRUE);
	return (FALSE);
}

int	is_looking_down(float angle)
{
	if (angle < LEFT && angle > RIGHT_MIN)
		return (TRUE);
	return (FALSE);
}

int	is_looking_right(float angle)
{
	if (angle > UP || angle < DOWN)
		return (TRUE);
	return (FALSE);
}

int	is_looking_left(float angle)
{
	if (angle < UP && angle > DOWN)
		return (TRUE);
	return (FALSE);
}

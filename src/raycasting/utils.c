/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:44:35 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/21 12:13:14 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_looking_up(t_player *player)
{
	if (player->dir > LEFT && player->dir < RIGHT_MAX)
		return (TRUE);
	return (FALSE);
}

int	is_looking_down(t_player *player)
{
	if (player->dir < LEFT && player->dir > RIGHT_MIN)
		return (TRUE);
	return (FALSE);
}

int	is_looking_right(t_player *player)
{
	if (player->dir > UP || player->dir < DOWN)
		return (TRUE);
	return (FALSE);
}

int	is_looking_left(t_player *player)
{
	if (player->dir < UP && player->dir > DOWN)
		return (TRUE);
	return (FALSE);
}

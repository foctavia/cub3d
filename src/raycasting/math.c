/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:26:00 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/22 17:35:03 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_angle_in_range(float *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	else if (*angle > 2 * PI)
		*angle -= 2 * PI;
}
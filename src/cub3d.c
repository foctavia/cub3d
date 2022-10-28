/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:01:50 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/28 16:44:56 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;
	
	if (argc != 2)
		return (ft_error(ERR_ARGS_COUNT, 0, NULL));
	if (ft_init(argv, &game))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

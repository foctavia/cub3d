/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:01:50 by owalsh            #+#    #+#             */
/*   Updated: 2022/12/01 17:20:12 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
		ft_error(ERR_ARGS_COUNT, 0, NULL, &game);
	ft_start(argv, &game);
	ft_mlx(&game);
	ft_clean(&game);
	return (EXIT_SUCCESS);
}

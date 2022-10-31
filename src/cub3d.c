/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:01:50 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/31 18:04:54 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		ft_error(ERR_ARGS_COUNT, 0, NULL, &game);
	ft_parse_init(argv, &game);
	ft_clean(&game);
	return (EXIT_SUCCESS);
}

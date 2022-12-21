/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:31:57 by owalsh            #+#    #+#             */
/*   Updated: 2022/12/21 13:21:58 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_arg(t_game *game, char **argv)
{
	if (!argv || !argv[0] || !argv[1])
		exit(EXIT_FAILURE);
	if (file_extension(argv[1], ".cub"))
		ft_error(ERR_WRONG_FILE_EXTENSION, 0, argv[1], game);
	if (open_file(game, argv[1]) == -1)
		ft_error(0, errno, argv[1], game);
}

int	ft_start(char **argv, t_game *game)
{
	check_arg(game, argv);
	init_game(game, argv[1]);
	if (ft_parse(game))
		exit(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

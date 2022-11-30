/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:35:59 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 21:04:59 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_parse(t_game *game)
{
	int		line_index;

	line_index = 0;
	game->file = copy_file(game);
	get_identifiers(game, game->file, &line_index);
	parse_map(game, game->file, &line_index);
	copy_map(game, game->file, &line_index);
	checker_map(game, line_index);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:29:40 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/03 09:26:44 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(int code, int err, char *arg, t_game *game)
{
	write(STDERR_FILENO, "Error\n", 7);
	if (arg)
	{
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": ", 2);
	}
	if (code == ERR_MALLOC)
		write(STDERR_FILENO, "malloc failed\n", 14);
	if (code == ERR_ARGS_COUNT)
		write(STDERR_FILENO, "invalid number of arguments\n", 28);
	else if (code == ERR_WRONG_FILE_EXTENSION)
		write(STDERR_FILENO, \
			"wrong file extension provided. expected: *.cub file.\n", 53);
	else if (code == ERR_MAP_WRONGID)
		write(STDERR_FILENO, "unexpected identifier in map\n", 29);
	else if (code == ERR_MAP_UNEXPECTED)
		write(STDERR_FILENO, "unexpected data in map\n", 23);
	else if (code == ERR_MAP_INCOMPLETEID)
		write(STDERR_FILENO, "incomplete information in identifier\n", 37);
	else if (code == ERR_TOOMANY_ID)
		write(STDERR_FILENO, \
			"one identifier has been encountered more than once\n", 51);
	else if (code == ERR_MAP_WALL)
		write(STDERR_FILENO, "map should be surrounded by walls\n", 34);
	else if (code == ERR_FORBIDDEN_CHAR)
		write(STDERR_FILENO, "map contains a forbidden character\n", 35);
	else if (code == ERR_RGB)
		write(STDERR_FILENO, "rgb color range: 0-255\n", 23);
	else if (err)
	{
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		return (err);
	}
	ft_clean(game);
	exit(EXIT_FAILURE);
}

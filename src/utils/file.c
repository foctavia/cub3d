/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:15:22 by owalsh            #+#    #+#             */
/*   Updated: 2022/12/21 13:33:27 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_file(t_game *game, char *path)
{
	int	fd;

	fd = open(path, __O_DIRECTORY);
	if (fd != -1)
		ft_error(ERR_OPENDIR, 0, path, game);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error(0, errno, path, game);
	return (fd);
}

int	file_extension(char *file, char *extension)
{
	int	i;
	int	j;

	i = ft_strlen(file) - 1;
	j = ft_strlen(extension) - 1;
	while (i && j && file[i] == extension[j])
	{
		i--;
		j--;
	}
	if (j == 0 && file[i] == extension[j])
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

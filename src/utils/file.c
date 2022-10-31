/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:15:22 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/31 15:21:26 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
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

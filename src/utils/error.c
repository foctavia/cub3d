/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:29:40 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/28 17:36:46 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(int code, int errno, char *arg)
{
	write(STDERR_FILENO, "Error\n", 7);
	if (arg)
	{
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": ", 2);
	}
	if (code == ERR_ARGS_COUNT)
		write(STDERR_FILENO, "invalid number of arguments\n", 28);
	else if (code == ERR_MAP_WRONGID)
		write(STDERR_FILENO, "unexpected identifier in map\n", 27);
	else if (code == ERR_MAP_INCOMPLETEID)
		write(STDERR_FILENO, "incomplete information in identifier\n", 37);
	else if (errno)
	{
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		return (errno);		
	}
	return (EXIT_FAILURE);
}

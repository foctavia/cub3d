/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:01:42 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/31 15:32:57 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "defines.h"
# include "structs.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
	
/*
** UTILS
*/
int		is_space(char c);
int		is_digit(char c);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strlen(char *str);
int		ft_error(int code, int err, char *arg, t_game *game);
int		file_extension(char *file, char *extension);
int		open_file(char *path);
char	*ft_strndup(const char *s, int n);
char	*ft_strjoin(char *s1, char *s2, int clean);
char	*get_next_line(int fd);
void	*ft_memset(void *s, int c, size_t n);
void	ft_clean(t_game *game);
/*
** PARSING
*/
int		ft_parse_init(char **argv, t_game *game);
int		ft_parse(t_game *game);

#endif
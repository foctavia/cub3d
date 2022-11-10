/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:01:42 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/10 15:22:39 by owalsh           ###   ########.fr       */
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
int		ft_error_map(int code, char *arg, t_game *game);
int		ft_error_mlx(int code, t_game *game);
int		file_extension(char *file, char *extension);
int		open_file(char *path);
char	*ft_strndup(const char *s, int n);
char	*ft_strjoin(char *s1, char *s2, int clean);
char	*get_next_line(int fd);
void	*ft_memset(void *s, int c, size_t n);
void	ft_clean(t_game *game);
void	display_map(t_map *map);
/*
** PARSING
*/
int		ft_parse_init(char **argv, t_game *game);
int		ft_parse(t_game *game);
int		check_identifier(char *str);
int		add_color(int id, char *line, int *i, t_game *game);
int		add_texture(int id, char *line, int *i, t_game *game);
int		get_map_content(int fd, t_game *game);
int		is_player(char c);
char	**copy_file(t_game *game);
void	get_identifiers(t_game *game, char **tab, int *line);
void	parse_map(t_game *game, char **tab, int *line);
void	copy_map(t_game *game, char **file, int *line_index);
void	checker_map(t_game *game, int line_index);
void	check_walls(t_game *game, char **content);
/*
** RENDERING
*/
void	ft_play(t_game *game);

#endif
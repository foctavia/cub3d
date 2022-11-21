/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:01:42 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/21 15:39:25 by foctavia         ###   ########.fr       */
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
# include <math.h>
	
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
void	display_player(t_game *game);
/*
** PARSING
*/
int		ft_start(char **argv, t_game *game);
int		ft_parse_init(char **argv, t_game *game);
int		ft_parse(t_game *game);
int		check_identifier(char *str);
int		add_color(int id, char *line, int *i, t_game *game);
int		add_texture(int id, char *line, int *i, t_game *game);
int		get_map_content(int fd, t_game *game);
int		is_player(char c);
char	**copy_file(t_game *game);
void	init_game(t_game *game, char *path);
void	get_identifiers(t_game *game, char **tab, int *line);
void	parse_map(t_game *game, char **tab, int *line);
void	copy_map(t_game *game, char **file, int *line_index);
void	checker_map(t_game *game, int line_index);
void	check_walls(t_game *game, char **content);
/*
** RENDERING
*/
int		is_wall(t_game *game, float dest_x, float dest_y);
int		key_hook(int keycode, t_game *game);
int		close_window(t_game *game);
int		assign_player_pos(t_game *game, t_elem elem, char c);
int		ft_render(t_game *game);
int		change_player_dir(t_player *player, int key);
void	assign_minimap_size(t_game *game, t_minimap *minimap);
void	draw_lines(t_game *game);
void	draw_square(t_game *game, t_elem elem, t_img *img);
void	draw_player(t_game *game, t_img *img, t_coord dest, int color);
void	put_pixel(t_game *game, t_img *img, t_coord coord, int color);
void	bresenham(t_game *game, t_coord coord1, t_coord coord2, int color);
void	ft_mlx(t_game *game);
/*
** RAYCASTING
*/
int		is_looking_right(float angle);
int		is_looking_left(float angle);
int		is_looking_up(float angle);
int		is_looking_down(float angle);
int		is_pixel_in_window_range(t_game *game, t_coord coord);
int		get_grid_coord(t_game *game, int pixel, int axis);
void	ft_raycast(t_game *game, t_player *player);
void	bresenham_pixel(t_game *game, t_coord coord1, t_coord coord2, int color);
t_coord	get_horizontal_ray(t_game *game, t_player *player, float ray_dir);
t_coord	get_vertical_ray(t_game *game, t_player *player, float ray_dir);

#endif
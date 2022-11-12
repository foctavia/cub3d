/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:16:02 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/12 19:08:12 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_texture
{
	char	*south;
	char	*north;
	char	*west;
	char	*east;
}				t_texture;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}				t_color;

typedef struct	s_img
{
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*addr;
	void	*img;
}				t_img;

typedef struct s_checker
{
	int		player;
	int			no;
	int			so;
	int			we;
	int			ea;
	int			f;
	int			c;
}				t_checker;

typedef struct s_map
{
	int			height;
	int			width;
	char		**content;
	t_color 	*floor;
	t_color		*ceiling;
	t_texture	*texture;
	t_checker	*checker;
}				t_map;

typedef struct	s_square
{
	int	x;
	int	y;
	int	side;
	int	color;
}				t_square;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	int		width;
	int		height;
}				t_mlx;

typedef struct s_game 
{
	int			err;
	char		*path;
	char		**file;
	t_map		*map;
	t_mlx		*mlx;
	t_img		*img;
}				t_game;

#endif

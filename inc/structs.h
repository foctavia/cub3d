/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:16:02 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/29 18:58:58 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
	int	hex;
}				t_color;

typedef struct	s_img
{
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*addr;
	void	*img;
}				t_img;

typedef struct	s_minimap
{
	float	width;
	float	height;
	float	elem_size;
}				t_minimap;

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


typedef struct	s_coord
{
	double	x;
	double	y;	
}				t_coord;

typedef struct s_map
{
	int			height;
	int			width;
	char		**content;
	t_color 	*floor;
	t_color		*ceiling;
	t_checker	*checker;
}				t_map;

typedef struct	s_elem
{
	int	x;
	int	y;
	int	side;
	int	color;
}				t_elem;

typedef struct	s_texture
{
	t_coord	pos;
	t_img	*img;
	char	*path;
	float	step;
	float	offset;
	int		width;
	int		height;
	int		id;
}				t_texture;

typedef struct s_mlx
{
	void		*mlx;
	void		*window;
	float		width;
	float		height;
	t_img		*img_3d;
	t_img		*img_minimap;
	t_minimap	*minimap;
}				t_mlx;

typedef struct	s_line
{
	int			height;
	int			start;
	int			end;
}				t_line;

typedef struct	s_ray
{
	t_coord		map;
	t_coord		dir;
	t_coord		side_dist;
	t_coord		delta_dist;
	t_coord		step;
	double		perpwall_dist;
	double		camera_x;
	int			side;
	int			hit;
	
}				t_ray;

typedef struct	s_time
{
	double		current;
	double		old;
	double		frame;
	double		move_speed;
	double		rot_speed;
}				t_time;

typedef struct	s_speed
{
	double		move;
	double		rotation;
}				t_speed;

typedef struct s_player
{
	double		delta_x;
	double		delta_y;
	t_coord		pos;
	t_coord		square;
	t_coord		plane;
	t_coord		dir;
	t_speed		speed;
}				t_player;

typedef struct s_game 
{
	int			err;
	char		*path;
	char		**file;
	t_map		*map;
	t_mlx		*mlx;
	t_player	*player;
	t_texture	*texture;
}				t_game;


#endif

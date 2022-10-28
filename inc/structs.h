/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:16:02 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/28 18:17:19 by owalsh           ###   ########.fr       */
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

typedef struct s_map
{
	int			no;
	int			so;
	int			we;
	int			ea;
	int			f;
	int			c;
	t_color 	*floor;
	t_color		*ceiling;
	t_texture	*texture;
	char		**content;	
}				t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
}				t_mlx;

typedef struct s_game 
{
	t_map		*map;
	t_mlx		*mlx;
	int			err;
}				t_game;

#endif
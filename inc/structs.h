/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:16:02 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/31 17:50:10 by foctavia         ###   ########.fr       */
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

typedef struct	s_content
{
	int					start;
	int					end;
	char				*line;
	struct s_content	*next;
	struct s_content	*prev;
}				t_content;

typedef struct s_map
{
	int			no;
	int			so;
	int			we;
	int			ea;
	int			f;
	int			c;
	int			height;
	int			width;
	t_color 	*floor;
	t_color		*ceiling;
	t_texture	*texture;
	t_content	*content;	
}				t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
}				t_mlx;

typedef struct s_game 
{
	int			err;
	char		*path;
	t_map		*map;
	t_mlx		*mlx;
}				t_game;

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:47:10 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/14 12:14:39 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	1. faire la map depuis vu d en haut
	2. faire des lignes horizontales et verticales
	3. faire un point rouge le player
	4. calculer la diff entre la position du player et les plus petites et plus grandes lignes de mur 
	5. raycasting en c avec un petit chat orange
*/

void	my_mlx_pixel_put(t_game *game, t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x > game->mlx->width || y > game->mlx->height)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int draw_square(t_game *game, t_elem elem, t_img *img)
{
	int	i;
	int	j;

	if (game->mlx->window == NULL)
		return (1);
	i = elem.x;
	while (i < elem.x + elem.side)
	{
		j = elem.y;
		while (j < elem.y + elem.side)
		{
			my_mlx_pixel_put(game, img, i, j, elem.color);
			j++;
		}
		i++;
	}
	return (0);
}

int	draw_player(t_game *game, t_elem elem, t_img *img)
{
	int		radius;
	double	i;
	double	x;
	double	y;
	
	radius = elem.side / 2;
	elem.color = 0xFF0000;
	i = 0;
	while (i < 360)
	{
		x = radius * 0.6 * cos(i * M_PI / 180);
        y = radius * 0.6 * sin(i * M_PI / 180);
		my_mlx_pixel_put(game, img, elem.x + radius + x, elem.y + radius + y, elem.color);
		i += 0.1;
	}
	return (EXIT_SUCCESS);
}

void	render_map(t_game *game, t_map *map, t_img *img)
{
	int	x;
	int	y;
	t_elem	elem;

	y = 0;
	if (game->map->height > game->map->width)
		elem.side = game->mlx->height / game->map->height;
	else
		elem.side = game->mlx->width / game->map->width;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			elem.x = x * elem.side;
			elem.y = y * elem.side;
			if (map->content[y][x] == GROUND)
				elem.color = 0x000000;
			else if (map->content[y][x] == WALL)
				elem.color = 0xFFFFFF;
			else if (is_player(map->content[y][x]))
				draw_player(game, elem, img);
			if (map->content[y][x] != ' ' && !is_player(map->content[y][x]))
				draw_square(game, elem, img);
			x++;
		}
		y++;
	}
}

void	ft_play(t_game *game)
{
	t_img	img;
	
	game->mlx->mlx = mlx_init();
	if (!game->mlx->mlx)
		ft_error_mlx(ERR_MLX_INIT, game);
	assign_win_size(game);
	game->mlx->window = mlx_new_window(game->mlx->mlx, \
		game->mlx->width, game->mlx->height, "CUB3D");
	if (!game->mlx->window)
		ft_error_mlx(ERR_MLX_WIN, game);
	img.img = mlx_new_image(game->mlx->mlx, game->mlx->width, game->mlx->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	game->img = &img;
	render_map(game, game->map, game->img);							
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->window, game->img->img, 0, 0);
	mlx_hook(game->mlx->window, 33, 1L << 2, &close_window, game);
	mlx_loop(game->mlx->mlx);
}

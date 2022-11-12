/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:47:10 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/12 19:17:26 by owalsh           ###   ########.fr       */
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

int	close_mlx(t_game *game)
{
	if (game && game->mlx && game->mlx->mlx)
		mlx_loop_end(game->mlx->mlx);
	if (game && game->mlx && game->mlx->window)
		mlx_destroy_window(game->mlx->mlx, game->mlx->window);
	if (game && game->mlx && game->mlx->mlx)
	{
		mlx_destroy_display(game->mlx->mlx);
		free(game->mlx->mlx);	
	}
	ft_clean(game);
	exit (EXIT_SUCCESS);
}

void	assign_win_size(t_game *game)
{
	int	width;
	int	height;
	float	ratio;

	mlx_get_screen_size(game->mlx->mlx, &width, &height);
	if (game->map->width > game->map->height)
	{
		game->mlx->width = width * 0.8;
		ratio = (float)game->map->height / game->map->width;
		game->mlx->height = ratio * game->mlx->width;
	}
	else
	{
		game->mlx->height = height * 0.8;
		ratio = (float)game->map->width / game->map->height;
		game->mlx->width = ratio * game->mlx->height;
	}
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int draw_square(t_game *game, t_square square, t_img *img)
{
	int	i;
	int j;

	if (game->mlx->window == NULL)
		return (1);
	i = square.y;
	while (i < square.y * square.side)
	{
		j = square.x;
		while (j < square.x * square.side)
			my_mlx_pixel_put(img, j++, i, square.color);
		++i;
	}
	return (0);
}

void	render_map(t_game *game, t_map *map, t_img *img)
{
	int	x;
	int	y;
	t_square	square;

	y = 0;
	if (game->map->height > game->map->width)
		square.side = game->mlx->height / game->map->height;
	else
		square.side = game->mlx->width / game->map->width;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			square.x = x;
			square.y = y;
			if (map->content[y][x] == GROUND)
				square.color = 0x000000;
			else if (map->content[y][x] == WALL)
				square.color = 0xFFFFFF;
			draw_square(game, square, img);
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
	mlx_hook(game->mlx->window, 33, 1L << 2, &close_mlx, game);
	mlx_loop(game->mlx->mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:47:10 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/12 16:26:29 by foctavia         ###   ########.fr       */
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

void	assign_win_size(t_mlx *mlx)
{
	int	width;
	int	height;

	mlx_get_screen_size(mlx->mlx, &width, &height);
	mlx->width = width * 0.8;
	mlx->height = height * 0.8;
}

void	render_map(t_game *game, t_map *map, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			draw(game, img, x, y);
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
	assign_win_size(game->mlx);
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

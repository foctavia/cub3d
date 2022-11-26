/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:35:06 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/26 17:34:46 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_buffer(t_game *game)
{
	int	y;
	int	x;

	game->mlx->buffer = malloc(sizeof(char *) * (game->mlx->height + 1));
	if (!game->mlx->buffer)
		ft_error(ERR_MALLOC, 0, NULL, game);
	y = 0;
	while (y < game->mlx->height)
	{
		game->mlx->buffer[y] = malloc(sizeof(char) * (game->mlx->width + 1));
		if (!game->mlx->buffer[y])
			ft_error(ERR_MALLOC, 0, NULL, game);
		y++;
	}
	y = 0;
	while (y < game->mlx->height)
	{
		x = 0;
		while (x < game->mlx->width)
		{
			game->mlx->buffer[y][x] = 0;
			x++;			
		}
		game->mlx->buffer[y][x] = '\0';
	}
	game->mlx->buffer[y] = NULL;
}

void	ft_mlx(t_game *game)
{
	t_img	img_minimap;
	t_img	img_3d;

	game->mlx->mlx = mlx_init();
	if (!game->mlx->mlx)
		ft_error_mlx(ERR_MLX_INIT, game);
	assign_mlx_size(game);
	game->mlx->window = mlx_new_window(game->mlx->mlx, \
		game->mlx->width, game->mlx->height, "cub3D");
	if (!game->mlx->window)
		ft_error_mlx(ERR_MLX_WIN, game);
	img_3d.img = mlx_new_image(game->mlx->mlx, \
		game->mlx->width, game->mlx->height);
	img_3d.addr = mlx_get_data_addr(img_3d.img, \
		&img_3d.bits_per_pixel, &img_3d.line_length, &img_3d.endian);
	game->mlx->img_3d = &img_3d;
	assign_minimap_size(game, game->mlx->minimap);
	img_minimap.img = mlx_new_image(game->mlx->mlx, \
		game->mlx->minimap->width, game->mlx->minimap->height);
	img_minimap.addr = mlx_get_data_addr(img_minimap.img, \
		&img_minimap.bits_per_pixel, &img_minimap.line_length, \
		&img_minimap.endian);
	game->mlx->img_minimap = &img_minimap;
	init_buffer(game);
	mlx_loop_hook(game->mlx->mlx, ft_render, game);
	mlx_hook(game->mlx->window, 2, 1L << 0, &key_hook, game);
	mlx_hook(game->mlx->window, 33, 1L << 2, &close_window, game);
	mlx_loop(game->mlx->mlx);
}

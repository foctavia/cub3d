/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:35:06 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/27 17:32:27 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx_buffer(t_game *game, t_mlx *mlx)
{
	int		i;
	int		j;

	mlx->buffer = (int **)malloc(sizeof(int *) * mlx->height);
	if (!mlx->buffer)
		ft_error(ERR_MALLOC, 0, NULL, game);
	i = 0;
	while (i < mlx->height)
	{
		mlx->buffer[i] = (int *)malloc(sizeof(int) * mlx->width);
		if (!mlx->buffer[i])
			ft_error(ERR_MALLOC, 0, NULL, game);
		i++;
	}
	i = 0;
	while (i < mlx->height)
	{
		j = 0;
		while (j < mlx->width)
		{
			mlx->buffer[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	ft_mlx(t_game *game)
{
	t_img	img_minimap;
	t_img	img_3d;

	game->mlx->mlx = mlx_init();
	if (!game->mlx->mlx)
		ft_error_mlx(ERR_MLX_INIT, game);
	assign_mlx_size(game);
	init_mlx_buffer(game, game->mlx);
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
	mlx_loop_hook(game->mlx->mlx, ft_render, game);
	mlx_hook(game->mlx->window, 2, 1L << 0, &key_hook, game);
	mlx_hook(game->mlx->window, 33, 1L << 2, &close_window, game);
	mlx_loop(game->mlx->mlx);
}

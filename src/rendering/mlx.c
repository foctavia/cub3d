/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:35:06 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 10:47:44 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_game *game, t_texture **texture)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		texture[i]->img.img = mlx_xpm_file_to_image(game->mlx->mlx, texture[i]->path, \
			&texture[i]->width, &texture[i]->height);
		texture[i]->img.addr = mlx_get_data_addr(texture[i]->img.img, \
			&texture[i]->img.bits_per_pixel, &texture[i]->img.line_length, &texture[i]->img.endian);
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
	load_texture(game, game->texture);
	mlx_loop_hook(game->mlx->mlx, ft_render, game);
	mlx_hook(game->mlx->window, 2, 1L << 0, &key_hook, game);
	mlx_hook(game->mlx->window, 33, 1L << 2, &close_window, game);
	mlx_loop(game->mlx->mlx);
}

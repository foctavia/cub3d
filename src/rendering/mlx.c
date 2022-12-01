/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:35:06 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 21:37:39 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(t_game *game, t_texture **texture)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		texture[i]->img.img = mlx_xpm_file_to_image(game->mlx->mlx,
				texture[i]->path, &texture[i]->width, &texture[i]->height);
		texture[i]->img.addr = mlx_get_data_addr(texture[i]->img.img,
				&texture[i]->img.bits_per_pixel, &texture[i]->img.line_length,
				&texture[i]->img.endian);
		i++;
	}
}

void	load_img(t_mlx	*mlx)
{
	mlx->img_3d.img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->img_3d.addr = mlx_get_data_addr(mlx->img_3d.img,
			&mlx->img_3d.bits_per_pixel, &mlx->img_3d.line_length,
			&mlx->img_3d.endian);
	mlx->img_minimap.img = mlx_new_image(mlx->mlx,
			mlx->minimap->width, mlx->minimap->height);
	mlx->img_minimap.addr = mlx_get_data_addr(mlx->img_minimap.img,
			&mlx->img_minimap.bits_per_pixel, &mlx->img_minimap.line_length,
			&mlx->img_minimap.endian);
}

void	ft_mlx(t_game *game)
{
	game->mlx->mlx = mlx_init();
	if (!game->mlx->mlx)
		ft_error_mlx(ERR_MLX_INIT, game);
	assign_mlx_size(game);
	game->mlx->window = mlx_new_window(game->mlx->mlx, \
		game->mlx->width, game->mlx->height, "cub3D");
	if (!game->mlx->window)
		ft_error_mlx(ERR_MLX_WIN, game);
	assign_minimap_size(game, game->mlx->minimap);
	load_img(game->mlx);
	load_texture(game, game->texture);
	mlx_hook(game->mlx->window, 2, 1L << 0, &key_press, game);
	mlx_hook(game->mlx->window, 33, 1L << 2, &close_window, game);
	mlx_hook(game->mlx->window, 3, 1L << 1, &key_release, game);
	mlx_loop_hook(game->mlx->mlx, ft_render, game);
	mlx_loop(game->mlx->mlx);
}

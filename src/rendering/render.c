/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:47:10 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/15 14:57:29 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	assign_player_pos(t_game *game, char c)
{
	if (c == NORTH_DIR)
		game->player->dir = NORTH_DIR;
	else if (c == SOUTH_DIR)
		game->player->dir = SOUTH_DIR;
	else if (c == WEST_DIR)
		game->player->dir = WEST_DIR;
	else if (c == EAST_DIR)
		game->player->dir = EAST_DIR;
	return (TRUE);
}

void	render_minimap(t_game *game, t_map *map, t_img *img, t_player *player)
{
	int		x;
	int		y;
	t_elem	elem;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			elem.x = x * game->mlx->elem_size;
			elem.y = y * game->mlx->elem_size;
			if (map->content[y][x] == GROUND)
				elem.color = HEX_BLACK;
			else if (map->content[y][x] == WALL)
				elem.color = HEX_WHITE;
			else if (!player && is_player(map->content[y][x]) 
				&& assign_player_pos(game, map->content[y][x]))
				put_player(game, elem, img);
			else if (player)
				render_player(game, game->mlx->minimap, player->pos, HEX_RED);
			if (map->content[y][x] != ' ' && !is_player(map->content[y][x]))
				draw_square(game, elem, img);
			x++;
		}
		y++;
	}
	draw_line(game);
}

void	ft_render(t_game *game)
{
	t_img	img;

	game->mlx->mlx = mlx_init();
	if (!game->mlx->mlx)
		ft_error_mlx(ERR_MLX_INIT, game);
	assign_mlx_size(game);
	game->mlx->window = mlx_new_window(game->mlx->mlx, \
		game->mlx->width, game->mlx->height, "CUB3D");
	if (!game->mlx->window)
		ft_error_mlx(ERR_MLX_WIN, game);
	img.img = mlx_new_image(game->mlx->mlx, \
		game->mlx->width, game->mlx->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
		&img.line_length, &img.endian);
	game->mlx->minimap = &img;
	render_minimap(game, game->map, game->mlx->minimap, NULL);
	mlx_put_image_to_window(game->mlx->mlx, \
		game->mlx->window, game->mlx->minimap->img, 0, 0);
	mlx_hook(game->mlx->window, 2, 1L << 0, &key_hook, game);
	mlx_hook(game->mlx->window, 33, 1L << 2, &close_window, game);
	mlx_loop(game->mlx->mlx);
}

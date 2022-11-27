/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:47:10 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/27 18:29:23 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_player(t_game *game, t_map *map, t_img *img, t_player *player)
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
			elem.x = x * game->mlx->minimap->elem_size;
			elem.y = y * game->mlx->minimap->elem_size;
			if (is_player(map->content[y][x]) && player && \
				player->pos.x == 0 && player->pos.y == 0)
				assign_player_pos(game, elem, map->content[y][x]);
			if (is_player(map->content[y][x]) && player)
				draw_player(game, img, player->pos, HEX_RED);
			x++;
		}
		y++;
	}
}

void	render_minimap(t_game *game, t_map *map, t_img *img)
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
			elem.x = x * game->mlx->minimap->elem_size;
			elem.y = y * game->mlx->minimap->elem_size;
			if (map->content[y][x] == GROUND)
				elem.color = HEX_BLACK;
			else if (map->content[y][x] == WALL)
				elem.color = HEX_WHITE;
			if (map->content[y][x] != ' ' && !is_player(map->content[y][x]))
				draw_square(game, elem, img);
			x++;
		}
		y++;
	}
	draw_lines(game);
}

void	cub_draw(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->mlx->height)
	{
		x = 0;
		while (x < game->mlx->width)
		{
			game->mlx->img_3d->addr[(int)y * game->mlx->img_3d->line_length \
				+ (int)x * (game->mlx->img_3d->bits_per_pixel / 8)]
				= game->mlx->buffer[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx->mlx, \
		game->mlx->window, game->mlx->img_3d->img, 0, 0);
}

int	ft_render(t_game *game)
{
	render_minimap(game, game->map, game->mlx->img_minimap);
	render_player(game, game->map, game->mlx->img_minimap, game->player);
	draw_floor_and_ceiling(game, game->mlx->img_3d);
	ft_raycast(game, game->player);
	// cub_draw(game);
	mlx_put_image_to_window(game->mlx->mlx, \
		game->mlx->window, game->mlx->img_3d->img, 0, 0);
	mlx_put_image_to_window(game->mlx->mlx, \
		game->mlx->window, game->mlx->img_minimap->img, \
		game->mlx->width - game->mlx->minimap->width, 0);
	return (EXIT_SUCCESS);
}

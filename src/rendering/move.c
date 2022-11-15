/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:52:35 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/15 18:42:50 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_player(t_game *game, t_img *img, t_coord dest, int color)
{
	t_coord	center;
	int		radius;
	double	i;
	double	x;
	double	y;

	radius = game->mlx->elem_size / 2;
	i = 0;
	while (i < 360)
	{
		x = radius * 0.1 * cos(i * M_PI / 180);
		y = radius * 0.1 * sin(i * M_PI / 180);
		center.x = dest.x + x;
		center.y = dest.y + y;
		put_pixel(game, img, center, color);
		i += 0.01;
	}
}

int	is_wall(t_game *game, float dest_x, float dest_y)
{
	float	square_x;
	float	square_y;

	square_y = dest_y * game->map->height / game->mlx->height;
	square_x = dest_x * game->map->width / game->mlx->width;
	if (game->map->content[(int)square_y][(int)square_x] == WALL)
		return (TRUE);
	return (FALSE);
}

void	change_direction(t_player *player, int key)
{
	if (key == KEY_RIGHT || key == KEY_D)
	{
		printf("in change direction with key right\n");
		if (player->dir == 360)
			player->dir = 0;
		player->dir += 90;
	}
	else if (key == KEY_LEFT || key == KEY_A)
	{
		printf("in change direction with key left\n");
		if (player->dir == 0)
			player->dir = 360;
		player->dir -= 90;
	}
	printf("player direction = %d\n", player->dir);
}

int	move(t_game *game, t_player *player)
{
	t_img	img;

	printf("in move with player direction = %d\n", player->dir);
	if (player->dir == RIGHT && !is_wall(game, player->pos.x + 5, player->pos.y))
		player->pos.x += 5;
	else if (player->dir == LEFT && !is_wall(game, player->pos.x - 5, player->pos.y))
		player->pos.x -= 5;
	else if (player->dir == DOWN && !is_wall(game, player->pos.x, player->pos.y + 5))
		player->pos.y += 5;
	else if (player->dir == UP && !is_wall(game, player->pos.x, player->pos.y - 5))
		player->pos.y -= 5;
	else
		return (EXIT_FAILURE);
	img.img = mlx_new_image(game->mlx->mlx, \
		game->mlx->width, game->mlx->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
		&img.line_length, &img.endian);
	game->mlx->minimap = &img;
	render_minimap(game, game->map, &img, player);
	mlx_put_image_to_window(game->mlx->mlx, \
		game->mlx->window, game->mlx->minimap->img, 0, 0);
	mlx_destroy_image(game->mlx->mlx, game->mlx->minimap->img);
	return (EXIT_SUCCESS);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_RIGHT || keycode == KEY_D)
		change_direction(game->player, keycode);
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		change_direction(game->player, keycode);
	else if (keycode == KEY_UP || keycode == KEY_W)
		return (move(game, game->player));
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		return (move(game, game->player));
	else if (keycode == KEY_ESC)
		return (close_window(game));
	return (EXIT_SUCCESS);
}

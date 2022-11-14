/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:52:35 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/14 18:04:30 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move(t_game *game, int x, int y, char dir)
{
	game->map->content[y][x] = '0';
	draw_player(game, game->tab[y][x], game->mlx->minimap);
	if (dir == 'R')
		x++;
	else if (dir == 'L')
		x--;
	else if (dir == 'U')
		y--;
	else if (dir == 'D')
		y++;
	game->map->content[y][x] = 'S';
	draw_square(game, game->tab[y][x], game->mlx->minimap);
	return (1);
}

int	move_right(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (game->map->content[y])
	{
		x = 0;
		while (game->map->content[y][x])
		{
			if (game->map->content[y][x] == 'S')
			{
				if (game->map->content[y][x + 1] == '0')
					return (move(game, x, y, 'R'));
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	move_left(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (game->map->content[y])
	{
		x = 0;
		while (game->map->content[y][x])
		{
			if (game->map->content[y][x] == 'S')
			{
				if (game->map->content[y][x - 1] == '0')
					return (move(game, x, y, 'L'));
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	move_up(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (game->map->content[y])
	{
		x = 0;
		while (game->map->content[y][x])
		{
			if (game->map->content[y][x] == 'S')
			{
				if (game->map->content[y - 1][x] == '0')
					return (move(game, x, y, 'U'));
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	move_down(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (game->map->content[y])
	{
		x = 0;
		while (game->map->content[y][x])
		{
			if (game->map->content[y][x] == 'P')
			{
				if (game->map->content[y + 1][x] == '0')
					return (move(game, x, y, 'D'));
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_RIGHT)
		return (move_right(game));
	else if (keycode == KEY_LEFT)
		return (move_left(game));
	else if (keycode == KEY_UP)
		return (move_up(game));
	else if (keycode == KEY_DOWN)
		return (move_down(game));
	else if (keycode == 65307)
		return (sl_close(game));
	return (0);
}

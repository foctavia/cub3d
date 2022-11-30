/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:24:21 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 21:41:09 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_D)
		game->player->move.right = 1;
	if (keycode == KEY_RIGHT)
		game->player->look.right = 1;
	if (keycode == KEY_A)
		game->player->move.left = 1;
	if (keycode == KEY_LEFT)
		game->player->look.left = 1;
	if (keycode == KEY_W)
		game->player->move.up = 1;
	if (keycode == KEY_UP)
		game->player->look.up = 1;
	if (keycode == KEY_S)
		game->player->move.down = 1;
	if (keycode == KEY_DOWN)
		game->player->look.down = 1;
	if (keycode == KEY_ESC)
		close_window(game);
	return (EXIT_SUCCESS);
}

int	key_release(t_game *game, int keycode)
{
	if (keycode == KEY_D)
		game->player->move.right = 0;
	if (keycode == KEY_RIGHT)
		game->player->look.right = 0;
	if (keycode == KEY_A)
		game->player->move.left = 0;
	if (keycode == KEY_LEFT)
		game->player->look.left = 0;
	if (keycode == KEY_W)
		game->player->move.up = 0;
	if (keycode == KEY_UP)
		game->player->look.up = 0;
	if (keycode == KEY_S)
		game->player->move.down = 0;
	if (keycode == KEY_DOWN)
		game->player->look.down = 0;
	return (EXIT_SUCCESS);
}

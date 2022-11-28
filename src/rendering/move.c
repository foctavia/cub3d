/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:52:35 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/28 18:05:59 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *game, float dest_x, float dest_y)
{
	float	square_x;
	float	square_y;

	square_y = dest_y / game->mlx->minimap->elem_size;
	square_x = dest_x / game->mlx->minimap->elem_size;
	if ((int)square_y < 0 || (int)square_x < 0 || \
		(int)square_y >= game->map->height || (int)square_x >= game->map->width)
		return (FALSE);
	if (game->map->content[(int)square_y][(int)square_x] == WALL)
		return (TRUE);
	return (FALSE);
}

static void	get_dest_coord(t_player *player, int key, t_coord *dest)
{
	dest->x = player->pos.x;
	dest->y = player->pos.y;
	if (key == KEY_UP)
	{
		dest->x += player->delta_x;
		dest->y += player->delta_y;
	}
	else if (key == KEY_DOWN)
	{
		dest->x -= player->delta_x;
		dest->y -= player->delta_y;
	}
}

int	change_player_pos(t_game *game, t_player *player, int key)
{
	t_coord	dest;

	get_dest_coord(player, key, &dest);
	if (is_wall(game, dest.x, dest.y))
		return (EXIT_FAILURE);
	draw_player(game, game->mlx->img_minimap, player->pos, HEX_BLACK);
	player->pos.x = dest.x;
	player->pos.y = dest.y;
	return (EXIT_SUCCESS);
}

int	move_player(t_game *game, t_player *player, int key)
{
	if (key == KEY_LEFT || key == KEY_RIGHT)
		change_player_dir(player, key);
	else
		change_player_pos(game, player, key);
	ft_render(game);
	return (EXIT_SUCCESS);
}

// void	move_up(t_game *game, t_player *player)
// {
	
// }

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_RIGHT || keycode == KEY_D)
		return (move_player(game, game->player, KEY_RIGHT));
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		return (move_player(game, game->player, KEY_LEFT));
	else if (keycode == KEY_UP || keycode == KEY_W)
		return (move_player(game, game->player, KEY_UP));
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		return (move_player(game, game->player, KEY_DOWN));
	else if (keycode == KEY_ESC)
		return (close_window(game));
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:33:46 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 21:02:04 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_texture_id(t_ray ray, t_player *player, int *id)
{
	(void)player;
	if (ray.side == SIDE_X && ray.dir.y >= 0)
		*id = 0;
	if (ray.side == SIDE_X && ray.dir.y < 0)
		*id = SOUTH_TEXTURE;
	if (ray.side == SIDE_Y && ray.dir.x >= 0)
		*id = WEST_TEXTURE;
	if (ray.side == SIDE_Y && ray.dir.x < 0)
		*id = EAST_TEXTURE;
}

static void	set_texture_data(t_game *game, t_texture *texture,
	t_ray ray, t_line line)
{
	double	wall_x;

	if (ray.side == SIDE_Y)
		wall_x = game->player->square.y + ray.perpwall_dist * ray.dir.y;
	else
		wall_x = game->player->square.x + ray.perpwall_dist * ray.dir.x;
	wall_x -= floor(wall_x);
	texture->coord.x = (int)(wall_x * (double)64);
	if (ray.side == SIDE_Y && ray.dir.x < 0)
		texture->coord.x = 64 - texture->coord.x - 1;
	if (ray.side == SIDE_X && ray.dir.y > 0)
		texture->coord.x = 64 - texture->coord.x - 1;
	texture->step = 1.0 * 64 / line.height;
	texture->pos = (line.start - game->player->pitch - game->mlx->height
			/ 2 + line.height / 2) * texture->step;
}

void	add_cool_line(t_game *game, t_coord *coord)
{
	if (!ft_strncmp(game->path, "maps/cool.cub", 14))
	{
		put_pixel(game, game->mlx->img_3d, *coord, HEX_GREEN);
		coord->y += 1;
	}
}

void	draw_texture(t_game *game, t_texture *texture, t_img img, t_coord coord)
{
	texture->coord.y = (int)texture->pos & (64 - 1);
	texture->pos += texture->step;
	if (is_in_range(game, coord.x, coord.y))
		game->mlx->img_3d.addr[((int)coord.y * game->mlx->img_3d.line_length
				+ (int)(coord.x * (game->mlx->img_3d.bits_per_pixel / 8)))]
			= img.addr[(((int)texture->coord.y * img.line_length)
				+ ((int)texture->coord.x * img.bits_per_pixel / 8))];
	if (is_in_range(game, coord.x, coord.y))
		game->mlx->img_3d.addr[((int)coord.y * game->mlx->img_3d.line_length
				+ (int)(coord.x * (game->mlx->img_3d.bits_per_pixel / 8))) + 1]
			= img.addr[(((int)texture->coord.y * img.line_length)
				+ ((int)texture->coord.x * img.bits_per_pixel / 8)) + 1];
	if (is_in_range(game, coord.x, coord.y))
		game->mlx->img_3d.addr[((int)coord.y * game->mlx->img_3d.line_length
				+ (int)(coord.x * (game->mlx->img_3d.bits_per_pixel / 8))) + 2]
			= img.addr[(((int)texture->coord.y * img.line_length)
				+ ((int)texture->coord.x * img.bits_per_pixel / 8)) + 2];
	if (is_in_range(game, coord.x, coord.y))
		game->mlx->img_3d.addr[((int)coord.y * game->mlx->img_3d.line_length
				+ (int)(coord.x * (game->mlx->img_3d.bits_per_pixel / 8))) + 3]
			= img.addr[(((int)texture->coord.y * img.line_length)
				+ ((int)texture->coord.x * img.bits_per_pixel / 8)) + 3];
}

void	draw(t_game *game, t_ray ray, t_line line, int x)
{
	t_texture	texture;
	t_coord		coord;
	t_img		img_3d;
	t_img		img;
	int			tex_id;

	ft_memset(&texture, 0, sizeof(t_texture));
	set_texture_data(game, &texture, ray, line);
	set_texture_id(ray, game->player, &tex_id);
	img = game->texture[tex_id]->img;
	img_3d = game->mlx->img_3d;
	coord.x = x;
	coord.y = -1;
	while (coord.y++ < line.start)
		put_pixel(game, img_3d, coord, game->map->ceiling->hex);
	while (coord.y++ < line.end)
		draw_texture(game, &texture, img, coord);
	add_cool_line(game, &coord);
	while (coord.y++ < game->mlx->height)
		put_pixel(game, img_3d, coord, game->map->floor->hex);
}

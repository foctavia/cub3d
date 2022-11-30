/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:33:46 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/30 18:08:27 by owalsh           ###   ########.fr       */
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
	texture->pos = (line.start - game->mlx->height / 2 + line.height / 2)
		* texture->step;
}

void	add_cool_line(t_game *game, int x, int y)
{
	t_coord coord;

	coord.x = x;
	coord.y = y;
	put_pixel(game, game->mlx->img_3d, coord, HEX_GREEN);
}

void	draw_texture(t_game *game, t_ray ray, t_line line, int x)
{
	t_texture	texture;
	t_img		*img_3d;
	t_img		img;
	int			tex_id;
	int			y;

	ft_memset(&texture, 0, sizeof(t_texture));
	set_texture_data(game, &texture, ray, line);
	set_texture_id(ray, game->player, &tex_id);
	img = game->texture[tex_id]->img;
	img_3d = game->mlx->img_3d;
	y = line.start;
	while (y < line.end)
	{
		texture.coord.y = (int)texture.pos & (64 - 1);
		texture.pos += texture.step;
		if (is_in_range(game, x, y))
			img_3d->addr[((int)y * img_3d->line_length
					+ (int)(x * (img_3d->bits_per_pixel / 8)))]
				= img.addr[(((int)texture.coord.y * img.line_length)
					+ ((int)texture.coord.x * img.bits_per_pixel / 8))];
		if (is_in_range(game, x, y))
			img_3d->addr[((int)y * img_3d->line_length
					+ (int)(x * (img_3d->bits_per_pixel / 8))) + 1]
				= img.addr[(((int)texture.coord.y * img.line_length)
					+ ((int)texture.coord.x * img.bits_per_pixel / 8)) + 1];
		if (is_in_range(game, x, y))
			img_3d->addr[((int)y * img_3d->line_length
					+ (int)(x * (img_3d->bits_per_pixel / 8))) + 2]
				= img.addr[(((int)texture.coord.y * img.line_length)
					+ ((int)texture.coord.x * img.bits_per_pixel / 8)) + 2];
		if (is_in_range(game, x, y))
			img_3d->addr[((int)y * img_3d->line_length
					+ (int)(x * (img_3d->bits_per_pixel / 8))) + 3]
				= img.addr[(((int)texture.coord.y * img.line_length)
					+ ((int)texture.coord.x * img.bits_per_pixel / 8)) + 3];
		y++;
	}
	if (!ft_strncmp(game->path, "maps/cool.cub", 14))
		add_cool_line(game, x, y);	
}

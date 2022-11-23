/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:08:45 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/23 18:40:32 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
      //x coordinate on the texture
      int texX = int(wallX * double(texWidth));
      if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
      if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
*/

int	get_texture_color(t_game *game, t_coord coord)
{
	t_img	text;
	char	*mlx_data_addr;
	int		color;
	int		width;
	int 	height;

	text.img = mlx_xpm_file_to_image(game->mlx->mlx, "purplestone.xpm", \
		&width, &height);
	text.addr = mlx_get_data_addr(text.img, 
		&text.bits_per_pixel, &text.line_length, &text.endian);
	// printf("text.img: %p\ttext.width: %d, text.height: %d\n", text.img, width, height);
	mlx_data_addr = text.addr + ((int)coord.y * text.line_length \
		+ (int)coord.x * (text.bits_per_pixel / 8));
	printf("mlx_data_addr: %p\n", mlx_data_addr);
	color = *(unsigned int *)mlx_data_addr;
	return (color);
}

void	draw_texture(t_game *game, t_coord coord1, t_coord coord2, int color)
{
	float	d_x;
	float	d_y;
	int		max;

	d_x = coord2.x - coord1.x;
	d_y = coord2.y - coord1.y;
	max = BIGGER(ABS(d_x), ABS(d_y));
	d_x /= max;
	d_y /= max;
	while ((int)(coord1.x - coord2.x) || (int)(coord1.y - coord2.y))
	{
		color = get_texture_color(game, coord1);
		put_pixel(game, game->mlx->img_3d, coord1, color);
		coord1.x += d_x;
		coord1.y += d_y;
	}
}

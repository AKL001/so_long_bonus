/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:41:03 by ablabib           #+#    #+#             */
/*   Updated: 2025/02/18 18:08:01 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

unsigned int	get_pixel_color(t_img *img, int x, int y)
{
	char	*pixel;

	if (!img || !img->addr)
		return (0);
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)pixel);
}

void	put_pixel_to_buffer(t_game *game, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= game->map_data.width
		|| y >= game->map_data.height)
		return ;
	dst = game->buffer.addr + (y * game->buffer.line_len + x * (game->buffer.bpp
				/ 8));
	*(unsigned int *)dst = color;
}

static int	get_image_size(t_game *game, t_img *img)
{
	if (img == &game->floor_img || img == &game->wall_img
		|| img == &game->door_open || img == &game->door_close)
		return (TILE_SIZE);
	if (img == &game->poke_ball.frames[0] || img == &game->poke_ball.frames[1]
		|| img == &game->poke_ball.frames[2]
		|| img == &game->poke_ball.frames[3])
		return (BALL_SIZE);
	if (img >= &game->player.top_frames[0]
		&& img <= &game->player.left_frames[3])
		return (SPIRIT_SIZE);
	if (img >= &game->monster_img.frames[0]
		&& img <= &game->monster_img.frames[3])
		return (SPIRIT_SIZE);
	return (TILE_SIZE);
}

void	draw_image_to_buffer(t_game *game, t_img *img, int start_x, int start_y)
{
	int				x;
	int				y;
	int				size;
	unsigned int	color;

	size = get_image_size(game, img);
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			color = get_pixel_color(img, x, y);
			if (color != 0xFF000000)
				put_pixel_to_buffer(game, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void	init_image(t_game *game, t_img *img, char *path)
{
	int	width;
	int	height;

	img->img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!img->img)
	{
		printf("Failed to load image: %s\n", path);
		close_window(game);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
	{
		printf("Failed to get image address: %s\n", path);
		close_window(game);
	}
}

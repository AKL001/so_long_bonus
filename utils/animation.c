/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:36:18 by ablabib           #+#    #+#             */
/*   Updated: 2025/02/16 21:36:19 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ball_animation(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_check.map_height)
	{
		x = 0;
		while (x < game->map_check.map_width)
		{
			if (game->map[y][x] == 'C')
			{
				draw_image_to_buffer(game, &game->floor_img, x * TILE_SIZE, y
					* TILE_SIZE);
				draw_image_to_buffer(game,
					&game->poke_ball.frames[game->poke_ball.current_frame], x
					* TILE_SIZE + BALL_SIZE / 2, y * TILE_SIZE + BALL_SIZE / 2);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->buffer.img, 0, 0);
}

static void	draw_monster(t_game *game, int x, int y)
{
	draw_image_to_buffer(game, &game->floor_img, x * TILE_SIZE, y * TILE_SIZE);
	draw_image_to_buffer(game,
		&game->monster_img.frames[game->monster_img.current_frame], x
		* TILE_SIZE + (TILE_SIZE - SPIRIT_SIZE) / 2, y * TILE_SIZE + (TILE_SIZE
			- SPIRIT_SIZE) / 2);
}

static void	draw_exit(t_game *game, int x, int y)
{
	draw_image_to_buffer(game, &game->floor_img, x * TILE_SIZE, y * TILE_SIZE);
	draw_image_to_buffer(game, &game->door_open, x * TILE_SIZE, y * TILE_SIZE);
}

void	monster_animation(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_check.map_height)
	{
		x = 0;
		while (x < game->map_check.map_width)
		{
			if (game->map[y][x] == 'M')
				draw_monster(game, x, y);
			else if (game->map[y][x] == 'E'
				&& game->map_check.c == game->player_collects)
				draw_exit(game, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->buffer.img, 0, 0);
}

int	update_ball_animation(t_game *game)
{
	static int	frame = 0;
	static int	i = 0;
	static int	dirr = 1;

	frame++;
	if (frame >= 120)
	{
		game->poke_ball.current_frame = i;
		game->monster_img.current_frame = i;
		if (i == 3)
			dirr = -1;
		if (i == 0)
			dirr = 1;
		i += dirr;
		frame = 0;
		return (1);
	}
	return (0);
}

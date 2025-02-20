/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:10:17 by ablabib           #+#    #+#             */
/*   Updated: 2025/02/18 18:11:14 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	clear_character_last_position(t_game *game)
{
	draw_image_to_buffer(game, &game->floor_img, game->player_last_x
		* TILE_SIZE, game->player_last_y * TILE_SIZE);
	draw_image_to_buffer(game, &game->floor_img, game->player_x * TILE_SIZE,
		game->player_y * TILE_SIZE);
}

void	find_player_poss(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_check.map_height)
	{
		x = 0;
		while (x < game->map_check.map_width)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
			}
			x++;
		}
		y++;
	}
}

void	draw_map_to_buffer(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_check.map_height)
	{
		x = 0;
		while (x < game->map_check.map_width)
		{
			draw_image_to_buffer(game, &game->floor_img, x * TILE_SIZE, y
				* TILE_SIZE);
			if (game->map[y][x] == '1')
				draw_image_to_buffer(game, &game->wall_img, x * TILE_SIZE, y
					* TILE_SIZE);
			else if (game->map[y][x] == 'E'
				&& game->map_check.c != game->player_collects)
				draw_image_to_buffer(game, &game->door_close, x * TILE_SIZE, y
					* TILE_SIZE);
			x++;
		}
		y++;
	}
}

static void	which_frame_to_load(t_game *game, int player_dirrection,
		t_img **current_frame)
{
	if (player_dirrection == 0)
		*current_frame = game->player.top_frames;
	else if (player_dirrection == 1)
		*current_frame = game->player.down_frames;
	else if (player_dirrection == 2)
		*current_frame = game->player.left_frames;
	else if (player_dirrection == 3)
		*current_frame = game->player.right_frames;
	else
		return ;
}

void	render(t_game *game)
{
	t_img	*current_frame;

	current_frame = game->player.down_frames;
	clear_character_last_position(game);
	if (game->render_time < 2)
	{
		draw_map_to_buffer(game);
		ball_animation(game);
		monster_animation(game);
		game->render_time++;
	}
	if (game->player.direction < 0 || game->player.direction > 3
		|| game->player.current_frame < 0 || game->player.current_frame > 3)
		return ;
	which_frame_to_load(game, game->player.direction, &current_frame);
	draw_image_to_buffer(game, &current_frame[game->player.current_frame],
		game->player_x * TILE_SIZE + (TILE_SIZE - SPIRIT_SIZE) / 2,
		game->player_y * TILE_SIZE + (TILE_SIZE - SPIRIT_SIZE) / 2);
	mlx_put_image_to_window(game->mlx, game->win, game->buffer.img, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:03:15 by ablabib           #+#    #+#             */
/*   Updated: 2025/02/18 22:03:16 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_window(game);
	else if (keycode == KEY_W)
		move_player(game, 0);
	else if (keycode == KEY_S)
		move_player(game, 1);
	else if (keycode == KEY_A)
		move_player(game, 2);
	else if (keycode == KEY_D)
		move_player(game, 3);
	return (0);
}

void	init_game_state(t_game *game, t_player *player, t_map_data *map_data,
		t_obj *ball)
{
	game->player = (*player);
	game->player_collects = 0;
	game->player_moves = 0;
	game->render_time = 1;
	game->poke_ball = (*ball);
	game->map_data = (*map_data);
	game->map_data.height = game->map_check.map_height * TILE_SIZE;
	game->map_data.width = game->map_check.map_width * TILE_SIZE;
	game->player.direction = 1;
	game->player.current_frame = 0;
	game->player.is_moving = 0;
}

int	handle_frame_updates(t_game *game, clock_t current_time,
		clock_t *last_frame)
{
	const double	frame_delay = 1000000 / 70.0;

	if (current_time - *last_frame < frame_delay)
		return (0);
	if (game->player.is_moving)
	{
		update_animation(game);
		render(game);
		*last_frame = current_time;
		return (1);
	}
	return (0);
}

int	handle_ball_updates(t_game *game, clock_t current_time,
		clock_t *last_ball_update)
{
	const double	ball_delay = 1000000 / 15.0;

	if (current_time - *last_ball_update >= ball_delay)
	{
		if (update_ball_animation(game))
		{
			ball_animation(game);
			monster_animation(game);
			*last_ball_update = current_time;
			return (1);
		}
	}
	return (0);
}

int	handle_monster_updates(t_game *game, clock_t current_time,
		clock_t *last_monster_update)
{
	const double	monster_delay = 1000000 / 2.0;

	if (current_time - *last_monster_update >= monster_delay)
	{
		move_monsters(game);
		*last_monster_update = current_time;
		return (1);
	}
	return (0);
}

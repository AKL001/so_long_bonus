/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:06:16 by ablabib           #+#    #+#             */
/*   Updated: 2025/02/18 18:06:17 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	calculate_new_position(t_game *game, int direction, int *new_x,
		int *new_y)
{
	*new_x = game->player_x;
	*new_y = game->player_y;
	if (direction == 0)
		*new_y = *new_y - 1;
	if (direction == 1)
		*new_y = *new_y + 1;
	if (direction == 2)
		*new_x = *new_x - 1;
	if (direction == 3)
		*new_x = *new_x + 1;
}

int	is_valid_move(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map_check.map_width)
		return (0);
	if (new_y < 0 || new_y >= game->map_check.map_height)
		return (0);
	if (game->map[new_y][new_x] == 'C')
	{
		game->player_collects++;
		game->map[new_y][new_x] = '0';
		return (1);
	}
	if (game->map[new_y][new_x] == '1')
		return (0);
	if (game->map[new_y][new_x] == 'E'
		&& game->player_collects == game->map_check.c)
	{
		printf("YOU WON\n");
		close_window(game);
	}
	else if (game->map[new_y][new_x] == 'E'
		&& game->player_collects != game->map_check.c)
		return (0);
	if (game->map[new_y][new_x] == 'M')
		you_lost(game);
	return (1);
}

void	update_player_position(t_game *game, int new_x, int new_y,
		int direction)
{
	game->player.direction = direction;
	game->player.is_moving = 1;
	game->player.current_frame = 0;
	game->player_last_x = game->player_x;
	game->player_last_y = game->player_y;
	game->player_x = new_x;
	game->player_y = new_y;
	game->player_moves++;
}

void	move_player(t_game *game, int direction)
{
	int	new_x;
	int	new_y;

	if (game->player.is_moving)
		return ;
	calculate_new_position(game, direction, &new_x, &new_y);
	if (!is_valid_move(game, new_x, new_y))
		return ;
	update_player_position(game, new_x, new_y, direction);
}

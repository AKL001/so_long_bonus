/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:08:40 by ablabib           #+#    #+#             */
/*   Updated: 2025/02/18 18:08:42 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	you_lost(t_game *game)
{
	printf("YOU LOST\n");
	close_window(game);
}

void	init_monsters(t_game *game)
{
	int	x;
	int	y;
	int	index;

	y = 0;
	index = 0;
	while (y < game->map_check.map_height)
	{
		x = 0;
		while (x < game->map_check.map_width)
		{
			if (game->map[y][x] == 'M')
			{
				game->enemy_move[index].x = x;
				game->enemy_move[index].y = y;
				game->enemy_move[index].direction = 1;
				index++;
			}
			x++;
		}
		y++;
	}
}

void	move_monsters(t_game *game)
{
	int	i;
	int	new_x;

	i = 0;
	while (i < game->map_check.m)
	{
		new_x = game->enemy_move[i].x + game->enemy_move[i].direction;
		if (game->map[game->enemy_move[i].y][new_x] == '1'
			|| game->map[game->enemy_move[i].y][new_x] == 'E'
			|| game->map[game->enemy_move[i].y][new_x] == 'M'
			|| game->map[game->enemy_move[i].y][new_x] == 'C')
			game->enemy_move[i].direction *= -1;
		else if (new_x == game->player_x
			&& game->enemy_move[i].y == game->player_y)
			you_lost(game);
		else
		{
			game->map[game->enemy_move[i].y][game->enemy_move[i].x] = '0';
			draw_image_to_buffer(game, &game->floor_img, game->enemy_move[i].x
				* TILE_SIZE, game->enemy_move[i].y * TILE_SIZE);
			game->enemy_move[i].x = new_x;
			game->map[game->enemy_move[i].y][new_x] = 'M';
		}
		i++;
	}
}

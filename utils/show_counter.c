/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_counter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:20:25 by ablabib           #+#    #+#             */
/*   Updated: 2025/02/18 21:20:40 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	show_counter(t_game *game)
{
	char	*counter;

	counter = ft_itoa(game->player_moves);
	if (!counter)
		return ;
	mlx_string_put(game->mlx, game->win, 50, 50, 0x000000, counter);
	free(counter);
}

void	update_animation(t_game *game)
{
	static int	frame_counter = 0;

	frame_counter++;
	if (frame_counter >= 4)
	{
		game->player.current_frame = (game->player.current_frame + 1)
			% FRAMES_PER_MOVEMENT;
		frame_counter = 0;
		if (game->player.current_frame == 0)
		{
			game->player.is_moving = 0;
			return ;
		}
	}
}

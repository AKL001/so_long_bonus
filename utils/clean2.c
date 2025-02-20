/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:10:01 by ablabib           #+#    #+#             */
/*   Updated: 2025/02/18 18:10:02 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_map(t_game *game)
{
	int	i;

	if (!game->map)
		return ;
	i = 0;
	if (game->map)
	{
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
		game->map = NULL;
	}
}

static void	cleanup_all_frames(t_game *game)
{
	cleanup_frames(game->mlx, game->player.top_frames, MAX_FRAMES);
	cleanup_frames(game->mlx, game->player.down_frames, MAX_FRAMES);
	cleanup_frames(game->mlx, game->player.left_frames, MAX_FRAMES);
	cleanup_frames(game->mlx, game->player.right_frames, MAX_FRAMES);
	cleanup_frames(game->mlx, game->poke_ball.frames, MAX_FRAMES);
	cleanup_frames(game->mlx, game->monster_img.frames, MAX_FRAMES);
}

void	cleanup_resources(t_game *game)
{
	if (!game)
		return ;
	cleanup_all_frames(game);
	if (game->floor_img.img)
		mlx_destroy_image(game->mlx, game->floor_img.img);
	if (game->wall_img.img)
		mlx_destroy_image(game->mlx, game->wall_img.img);
	if (game->door_open.img)
		mlx_destroy_image(game->mlx, game->door_open.img);
	if (game->door_close.img)
		mlx_destroy_image(game->mlx, game->door_close.img);
	if (game->buffer.img)
		mlx_destroy_image(game->mlx, game->buffer.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_map(game);
}

int	close_window(t_game *game)
{
	cleanup_resources(game);
	exit(0);
}

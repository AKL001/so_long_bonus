/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:06:30 by ablabib           #+#    #+#             */
/*   Updated: 2025/02/18 18:07:09 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	clear_player_images(t_game *game, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		if (game->player.top_frames[i].img)
			mlx_destroy_image(game->mlx, game->player.top_frames[i].img);
		if (game->player.down_frames[i].img)
			mlx_destroy_image(game->mlx, game->player.down_frames[i].img);
		if (game->player.left_frames[i].img)
			mlx_destroy_image(game->mlx, game->player.left_frames[i].img);
		if (game->player.right_frames[i].img)
			mlx_destroy_image(game->mlx, game->player.right_frames[i].img);
		i++;
	}
}

void	clear_poke_ball_images(t_game *game, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		if (game->poke_ball.frames[i].img)
			mlx_destroy_image(game->mlx, game->poke_ball.frames[i].img);
	}
}

void	clear_monster_images(t_game *game, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		if (game->monster_img.frames[i].img)
			mlx_destroy_image(game->mlx, game->monster_img.frames[i].img);
	}
}

void	free_images(t_game *game)
{
	if (game->floor_img.img)
		mlx_destroy_image(game->mlx, game->floor_img.img);
	if (game->wall_img.img)
		mlx_destroy_image(game->mlx, game->wall_img.img);
	if (game->door_open.img)
		mlx_destroy_image(game->mlx, game->door_open.img);
	if (game->door_close.img)
		mlx_destroy_image(game->mlx, game->door_close.img);
	clear_player_images(game, 4);
	clear_poke_ball_images(game, 4);
	clear_monster_images(game, 4);
}

void	cleanup_frames(void *mlx, t_img *frames, int count)
{
	int	i;

	if (!mlx || !frames)
		return ;
	i = 0;
	while (i < count)
	{
		if (frames[i].img)
			mlx_destroy_image(mlx, frames[i].img);
		i++;
	}
}

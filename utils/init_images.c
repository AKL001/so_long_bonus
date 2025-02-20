/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:07:30 by ablabib           #+#    #+#             */
/*   Updated: 2025/02/18 18:07:32 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_player_frames(t_game *game, t_player *player)
{
	init_image(game, &player->down_frames[0], "assets/new_character/Down2.xpm");
	init_image(game, &player->down_frames[1], "assets/new_character/Down1.xpm");
	init_image(game, &player->down_frames[2], "assets/new_character/Down3.xpm");
	init_image(game, &player->down_frames[3], "assets/new_character/Down4.xpm");
	init_image(game, &player->left_frames[0], "assets/new_character/Left2.xpm");
	init_image(game, &player->left_frames[1], "assets/new_character/Left1.xpm");
	init_image(game, &player->left_frames[2], "assets/new_character/Left3.xpm");
	init_image(game, &player->left_frames[3], "assets/new_character/Left4.xpm");
	init_image(game, &player->right_frames[0],
		"assets/new_character/Right2.xpm");
	init_image(game, &player->right_frames[1],
		"assets/new_character/Right1.xpm");
	init_image(game, &player->right_frames[2],
		"assets/new_character/Right3.xpm");
	init_image(game, &player->right_frames[3],
		"assets/new_character/Right4.xpm");
	init_image(game, &player->top_frames[0], "assets/new_character/Top2.xpm");
	init_image(game, &player->top_frames[1], "assets/new_character/Top1.xpm");
	init_image(game, &player->top_frames[2], "assets/new_character/Top3.xpm");
	init_image(game, &player->top_frames[3], "assets/new_character/Top4.xpm");
}

void	init_pokeball_frames(t_game *game, t_obj *ball)
{
	game->poke_ball.current_frame = 0;
	init_image(game, &ball->frames[0], "assets/new_ball/pokeball_1.xpm");
	init_image(game, &ball->frames[1], "assets/new_ball/pokeball_2.xpm");
	init_image(game, &ball->frames[2], "assets/new_ball/pokeball_3.xpm");
	init_image(game, &ball->frames[3], "assets/new_ball/pokeball_4.xpm");
}

void	init_monster_frames(t_game *game, t_obj *monster)
{
	game->monster_img.current_frame = 0;
	init_image(game, &monster->frames[0], "assets/npcs/monster1.xpm");
	init_image(game, &monster->frames[1], "assets/npcs/monster2.xpm");
	init_image(game, &monster->frames[2], "assets/npcs/monster3.xpm");
	init_image(game, &monster->frames[3], "assets/npcs/monster4.xpm");
}

int	init_game_resources(t_game *game)
{
	init_image(game, &game->floor_img, "assets/new_floors/floor.xpm");
	init_image(game, &game->wall_img, "assets/new_walls/wall.xpm");
	init_image(game, &game->door_close, "assets/doors/door_close.xpm");
	init_image(game, &game->door_open, "assets/doors/door_open.xpm");
	init_monster_frames(game, &game->monster_img);
	init_pokeball_frames(game, &game->poke_ball);
	init_player_frames(game, &game->player);
	return (1);
}

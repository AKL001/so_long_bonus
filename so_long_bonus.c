/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:02:21 by ablabib           #+#    #+#             */
/*   Updated: 2025/02/18 22:02:23 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

static void	init_all_structs(t_game *game, t_player *player, t_map *map,
		t_map_data *map_data)
{
	t_obj		ball;
	t_obj		monster;
	t_monster	enemy;

	memset(game, 0, sizeof(t_game));
	memset(player, 0, sizeof(t_player));
	memset(&enemy, 0, sizeof(t_monster));
	memset(&ball, 0, sizeof(t_obj));
	memset(&monster, 0, sizeof(t_obj));
	memset(map_data, 0, sizeof(t_map_data));
	memset(map, 0, sizeof(t_map));
	game->map_check = *map;
	init_game_state(game, player, map_data, &ball);
	game->monster_img = monster;
}

static int	update_game(t_game *game)
{
	static clock_t	last_frame = 0;
	static clock_t	last_ball_update = 0;
	static clock_t	last_monster_update = 0;
	clock_t			current_time;

	current_time = clock();
	show_counter(game);
	handle_ball_updates(game, current_time, &last_ball_update);
	handle_monster_updates(game, current_time, &last_monster_update);
	handle_frame_updates(game, current_time, &last_frame);
	return (1);
}

static int	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, game->map_data.width,
			game->map_data.height, "POKE");
	if (!game->win)
		return (0);
	game->buffer.img = mlx_new_image(game->mlx, game->map_data.width,
			game->map_data.height);
	if (!game->buffer.img)
		return (0);
	game->buffer.addr = mlx_get_data_addr(game->buffer.img, &game->buffer.bpp,
			&game->buffer.line_len, &game->buffer.endian);
	if (!game->buffer.addr)
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_game		game;
	t_player	player;
	t_map		map;
	t_map_data	map_data;
	t_obj		ball;

	if (argc < 2)
		return (1);
	init_all_structs(&game, &player, &map, &map_data);
	map_checker(&game, argv);
	if (game.map_check.map_width > 32 || game.map_check.map_height > 18)
		return (close_window(&game), 1);
	init_game_state(&game, &player, &map_data, &ball);
	if (!init_window(&game))
		return (close_window(&game), 1);
	if (!init_game_resources(&game))
		return (close_window(&game), 1);
	init_monsters(&game);
	render(&game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop_hook(game.mlx, update_game, &game);
	mlx_loop(game.mlx);
	cleanup_resources(&game);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_checker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:52:17 by ablabib           #+#    #+#             */
/*   Updated: 2025/02/18 17:52:46 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	free_map_dup(char **tmp, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(tmp[i++]);
	free(tmp);
}

void	flood_fill_c(t_game *game, char ***tmp, int y, int x)
{
	if (x < 0 || y >= game->map_check.map_height || y < 0
		|| x >= game->map_check.map_width || (*tmp)[y][x] == '1'
		|| game->map[y][x] == '1' || game->map[y][x] == 'E'
		|| game->map[y][x] == 'M')
		return ;
	(*tmp)[y][x] = '1';
	if (game->map[y][x] == 'C')
		game->map_check.collect_found++;
	flood_fill_c(game, tmp, y + 1, x);
	flood_fill_c(game, tmp, y - 1, x);
	flood_fill_c(game, tmp, y, x + 1);
	flood_fill_c(game, tmp, y, x - 1);
}

void	flood_fill_e(t_game *game, char ***tmp, int y, int x)
{
	if (x < 0 || y >= game->map_check.map_height || y < 0
		|| x >= game->map_check.map_width || (*tmp)[y][x] == '1'
		|| game->map[y][x] == '1' || game->map[y][x] == 'M')
		return ;
	(*tmp)[y][x] = '1';
	if (game->map[y][x] == 'E')
		game->map_check.exit_found = 1;
	flood_fill_e(game, tmp, y + 1, x);
	flood_fill_e(game, tmp, y - 1, x);
	flood_fill_e(game, tmp, y, x + 1);
	flood_fill_e(game, tmp, y, x - 1);
}

static void	reset_tmp_map(char **tmp, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			tmp[i][j] = '0';
			j++;
		}
		i++;
	}
}

int	map_valid_path(t_game *game)
{
	char	**tmp;

	game->map_check.collect_found = 0;
	game->map_check.exit_found = 0;
	tmp = init_map_dup(game->map_check.map_width, game->map_check.map_height);
	if (!tmp)
		return (0);
	find_player_poss(game);
	flood_fill_c(game, &tmp, game->player_y, game->player_x);
	if (game->map_check.collect_found != game->map_check.c)
	{
		free_map_dup(tmp, game->map_check.map_height);
		return (1);
	}
	reset_tmp_map(tmp, game->map_check.map_width, game->map_check.map_height);
	flood_fill_e(game, &tmp, game->player_y, game->player_x);
	if (game->map_check.exit_found != 1)
	{
		free_map_dup(tmp, game->map_check.map_height);
		return (1);
	}
	free_map_dup(tmp, game->map_check.map_height);
	return (0);
}

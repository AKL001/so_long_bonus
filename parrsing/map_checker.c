/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:30:28 by ablabib           #+#    #+#             */
/*   Updated: 2025/02/18 17:53:28 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_walls(char *line, int line_len, int line_count, int last_line)
{
	int	i;

	i = 0;
	if (line_count == 0 || last_line)
	{
		while (i < line_len)
		{
			if (line[i] != '1')
				return (1);
			i++;
		}
	}
	else
	{
		if (line[0] != '1' || line[line_len - 1] != '1')
			return (1);
	}
	return (0);
}

int	validate_characters_bonus(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'C' && line[i] != 'E'
			&& line[i] != 'P' && line[i] != '\n' && line[i] != 'M')
			return (1);
		i++;
	}
	return (0);
}

void	validate_characters(char *line)
{
	int	i;

	if (!line)
		return ;
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'C' && line[i] != 'E'
			&& line[i] != 'P' && line[i] != '\n')
			return ;
		i++;
	}
}

void	count_elements(char *line, t_game *game, int bonus)
{
	int	i;

	if (!line)
		return ;
	i = 0;
	while (line[i])
	{
		if (line[i] == 'P')
			game->map_check.p++;
		else if (line[i] == 'E')
			game->map_check.e++;
		else if (line[i] == 'C')
			game->map_check.c++;
		else if (line[i] == 'M' && bonus == 1)
			game->map_check.m++;
		i++;
	}
}

void	map_checker(t_game *game, char **argv)
{
	int	fd;

	game->map_check.p = 0;
	game->map_check.e = 0;
	game->map_check.c = 0;
	if (check_map_extension(argv))
		error_map(game);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_map(game);
	if (is_map_valid_mandatory(game, fd))
	{
		close(fd);
		error_map(game);
	}
	close(fd);
	check_map_elements(game, 1);
	game->map = allocate_map(game);
	fill_map(game, argv);
	if (check_map_last_line(game->map, game->map_check.map_width,
			game->map_check.map_height))
		error_map(game);
	if (map_valid_path(game))
		error_map(game);
}

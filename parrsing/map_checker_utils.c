/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:57:39 by ablabib           #+#    #+#             */
/*   Updated: 2025/02/18 17:57:41 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	fill_map(t_game *game, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_map(game, 0);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_strncpy(game->map[i], line, game->map_check.map_width);
		game->map[i][game->map_check.map_width] = '\0';
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
}

static int	process_map_line(char *line, int *first_line_len, t_game *game,
		int line_count)
{
	int	line_len;

	line_len = ft_strlen(line);
	if (line[line_len - 1] == '\n')
		line_len--;
	if (*first_line_len == -1)
		*first_line_len = line_len;
	else if (line_len != *first_line_len)
		return (free(line), 1);
	if (check_walls(line, line_len, line_count, 0)
		|| validate_characters_bonus(line))
		return (free(line), 1);
	count_elements(line, game, 1);
	return (0);
}

int	is_map_valid_mandatory(t_game *game, int fd)
{
	char	*line;
	int		first_line_len;
	int		line_count;

	first_line_len = -1;
	line_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (process_map_line(line, &first_line_len, game, line_count))
			return (1);
		free(line);
		line_count++;
		line = get_next_line(fd);
	}
	game->map_check.map_height = line_count;
	game->map_check.map_width = first_line_len;
	return (0);
}

void	check_map_elements(t_game *game, int bonus)
{
	if (game->map_check.p != 1)
		error_map(game, 3);
	if (game->map_check.e != 1)
		error_map(game, 3);
	if (game->map_check.c < 1)
		error_map(game, 3);
	if (game->map_check.m < 1 && bonus == 1)
		error_map(game, 3);
}

int	check_map_last_line(char **map, int map_width, int map_height)
{
	int	x;
	int	last_line;

	last_line = map_height - 1;
	x = 0;
	while (x < map_width)
	{
		if (map[last_line][x] != '1')
			return (1);
		x++;
	}
	return (0);
}

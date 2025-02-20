/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:55:43 by ablabib           #+#    #+#             */
/*   Updated: 2025/02/18 17:56:46 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_map_extension(char **av)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(av[1]);
	while (av[1][i])
	{
		if (av[1][i] == '.')
		{
			if (i == 0)
				i++;
			else if (ft_strncmp("ber", &av[1][i + 1], ft_strlen(&av[1][i
					+ 1])) != 0 || ft_strncmp("ber", &av[1][i + 1], 3) != 0)
				return (1);
		}
		i++;
	}
	if (len < 4 || ft_strcmp(&av[1][len - 4], ".ber") != 0)
		return (1);
	return (0);
}

void	clear_buffer(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_data.height)
	{
		x = 0;
		while (x < game->map_data.width)
		{
			put_pixel_to_buffer(game, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	error_map(t_game *game)
{
	printf("Error\n");
	close_window(game);
}

char	**init_map_dup(int width, int height)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = malloc(sizeof(char *) * height);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < height)
	{
		tmp[i] = malloc(sizeof(char) * width);
		if (!tmp[i])
		{
			while (i > 0)
				free(tmp[--i]);
			free(tmp);
			return (NULL);
		}
		j = 0;
		while (j < width)
			tmp[i][j++] = '0';
		i++;
	}
	return (tmp);
}

char	**allocate_map(t_game *game)
{
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * (game->map_check.map_height + 1));
	if (!map)
		error_map(game);
	i = 0;
	while (i < game->map_check.map_height)
	{
		map[i] = malloc(sizeof(char) * (game->map_check.map_width + 1));
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			printf("Error\n");
			return (NULL);
		}
		i++;
	}
	map[game->map_check.map_height] = NULL;
	return (map);
}

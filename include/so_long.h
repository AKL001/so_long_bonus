/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:11:22 by ablabib           #+#    #+#             */
/*   Updated: 2025/02/18 16:12:46 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../get_next_line/get_next_line.h"
# include "../mlx/minilibx-linux/mlx.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>

# define TILE_SIZE 60
# define SPIRIT_SIZE 47
# define BALL_SIZE 30
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_W 119
# define ESC 65307
# define MAX_FRAMES 4

/* ANIMATION */
// 8 or 5
# define ANIMATION_SPEED 8
# define ANIMATION_DELAY 24
# define FRAMES_PER_MOVEMENT 4
# define FRAMES_PER_SEC 4

typedef struct s_map
{
	int			w;
	int			s;
	int			p;
	int			e;
	int			c;
	int			m;
	int			map_width;
	int			map_height;
	int			collect_found;
	int			exit_found;
}				t_map;

typedef struct s_map_data
{
	int			width;
	int			height;
}				t_map_data;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_obj
{
	t_img		frames[4];
	int			current_frame;
}				t_obj;

typedef struct s_player
{
	t_img		top_frames[4];
	t_img		down_frames[4];
	t_img		right_frames[4];
	t_img		left_frames[4];
	int			current_frame;
	int			direction;
	int			is_moving;
	int			animation_frame;
}				t_player;

typedef struct s_monster
{
	int			x;
	int			y;
	int			direction;
}				t_monster;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	t_monster	enemy_move[100];
	t_map		map_check;
	t_map_data	map_data;
	t_player	player;
	t_obj		poke_ball;
	t_obj		monster_img;
	t_img		buffer;
	t_img		floor_img;
	t_img		wall_img;
	t_img		door_open;
	t_img		door_close;
	int			render_time;
	int			player_moves;
	int			player_collects;
	int			player_x;
	int			player_y;
	int			player_last_x;
	int			player_last_y;
}				t_game;

/* GET_NEXT_LINE */
char			*get_next_line(int fd);

/*  PARSSING */
void			find_player_poss(t_game *game);
char			**allocate_map(t_game *game);
void			fill_map(t_game *game, char **argv);
int				is_map_valid_mandatory(t_game *game, int fd);
void			check_map_elements(t_game *game, int bonus);
int				check_map_last_line(char **map, int map_width, int map_height);
int				check_map_extension(char **av);
int				check_walls(char *line, int line_len, int line_count,
					int last_line);
int				validate_characters_bonus(char *line);
void			count_elements(char *line, t_game *game, int bonus);
void			map_checker(t_game *game, char **argv);
int				map_valid_path(t_game *game);
char			**init_map_dup(int width, int height);

/* images */
int				init_game_resources(t_game *game);

/* SO_LONG UTILS */
int				key_press(int keycode, t_game *game);
void			init_game_state(t_game *game, t_player *player,
					t_map_data *map_data, t_obj *ball);
int				handle_frame_updates(t_game *game, clock_t current_time,
					clock_t *last_frame);
int				handle_ball_updates(t_game *game, clock_t current_time,
					clock_t *last_ball_update);
int				handle_monster_updates(t_game *game, clock_t current_time,
					clock_t *last_monster_update);

/* MOVEMENTS */
void			move_player(t_game *game, int direction);

/* DRAW WITH BUFFERED */
void			draw_image_to_buffer(t_game *game, t_img *img, int start_x,
					int start_y);
void			init_image(t_game *game, t_img *img, char *path);
void			render(t_game *game);
unsigned int	get_pixel_color(t_img *img, int x, int y);
void			put_pixel_to_buffer(t_game *game, int x, int y,
					unsigned int color);
void			init_image(t_game *game, t_img *img, char *path);

void			draw_map_to_buffer(t_game *game);

/* ANIMATION */
void			init_pokeball_frames(t_game *game, t_obj *ball);
void			ball_animation(t_game *game);
int				update_ball_animation(t_game *game);
void			init_monster_frames(t_game *game, t_obj *monster);
void			monster_animation(t_game *game);

void			move_monsters(t_game *game);
void			init_monsters(t_game *game);

void			update_player_frame(t_player *player);
void			update_animation(t_game *game);
void			init_player_frames(t_game *game, t_player *player);

/* FREE AND ETC */
void			free_images(t_game *game);
void			free_map(t_game *game);
void			you_lost(t_game *game);
void			cleanup_game(t_game *game);
int				close_window(t_game *game);
void			cleanup_resources(t_game *game);
// void			free_map(t_game *game);
void			cleanup_frames(void *mlx, t_img *frames, int count);
void			error_map(t_game *game, int status);

/* LIBFT */
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_itoa(int nbr);

/* COUNTER */
void			show_counter(t_game *game);

#endif

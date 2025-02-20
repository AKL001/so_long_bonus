NAME = so_long

NEXT = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c  
LIBFT = libft/ft_strcmp.c  libft/ft_strncmp.c libft/ft_strncpy.c libft/ft_itoa.c
UTILS = utils/animation.c utils/buffer.c utils/clean.c utils/clean2.c utils/enemy_movement.c utils/map_loader.c \
		utils/movement.c utils/init_images.c parrsing/flood_fill_checker.c parrsing/map_checker_utils.c parrsing/map_checker.c \
		parrsing/map_checker2.c utils/show_counter.c

SRC = so_long_bonus.c so_long_utils.c $(UTILS) $(NEXT) $(LIBFT)

INCLUDES = libmlx_Linux.a
CC = cc
CFLAGS = -Wextra -Wall -Werror

OBJ = $(SRC:.c=.o)

bonus: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(OBJ) -o $(NAME) $(INCLUDES) -Imlx_linux -lXext -lX11 -lm -lz -g

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean bonus

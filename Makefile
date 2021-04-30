# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: icikrikc <icikrikc@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/10 14:12:56 by icikrikc      #+#    #+#                  #
#    Updated: 2021/04/30 01:54:45 by icikrikc      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

GREEN = \033[38;5;2m
NORMAL = \033[38;5;255m
RED = \033[38;5;1m
BLUE = \033[38;5;4m

SRCS	=	utils/gnl/get_next_line.c utils/gnl/get_next_line_utils.c \
			main.c error.c init.c \
			parse.c parse_other.c map_handle.c map_check.c map_check_2.c\
			hooks.c move.c rotate.c \
			draw.c ray-casting.c texture.c sprite.c get_sprites.c \
			pixel_funcs.c bitmap.c\

OBJS	= $(SRCS:.c=.o)

NAME	= cub3D

GCC		= gcc

FLAGS	= -Wall -Wextra -Werror -fsanitize=address -g

HEADER_FILE = cub3d.h

MLX_DIR	= minilibx_opengl

MLX_LIB = libmlx.a

LIBFT_DIR = utils/libft

LIBFT_LIB = libft.a

LINKS = -framework OpenGL -framework AppKit

all:	$(NAME)

$(NAME):	$(OBJS)
	$(MAKE) bonus -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(GCC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT_DIR)/$(LIBFT_LIB) $(MLX_DIR)/$(MLX_LIB) $(LINKS)

%.o: %.c $(HEADER_FILE)
	@echo "$(GREEN)Compiling:$(NORMAL)"
	$(GCC) -c $< -o $(<:.c=.o)
	@echo "$(GREEN)Successfully compiled!$(NORMAL)"

clean:
	@echo "$(RED)Removing all object files...$(NORMAL)"
	rm -f $(OBJS)
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) clean
	@echo "$(GREEN)Succesfully removed all object files!$(NORMAL)"

fclean: clean
	@echo "$(RED)Removing libraries and bitmap file...$(NORMAL)"
	rm -f $(NAME)
	rm -f cub3d.bmp
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)Successfully removed libraries and bitmap file!$(NORMAL)"

re: fclean all

.PHONY:	clean fclean re bonus

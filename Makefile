# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: icikrikc <icikrikc@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/10 14:12:56 by icikrikc      #+#    #+#                  #
#    Updated: 2021/04/29 19:33:41 by icikrikc      ########   odam.nl          #
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

INCLUDE_H	= -I minilibx

MLX_DIR		=	minilibx_opengl

all:	$(NAME)

.PHONY:	clean fclean re bonus bench bclean

$(NAME):	$(OBJS)
	$(MAKE) bonus -C utils/libft
	$(MAKE) -C minilibx_opengl
	$(GCC) $(FLAGS) -o $(NAME) $(OBJS) -L utils/libft -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

clean:
	@echo "$(RED)Removing all object files...$(NORMAL)"
	rm -f $(OBJS)
	make clean -C ./utils/libft
	@echo "$(GREEN)Succesfully removed all object files!$(NORMAL)"

fclean: clean
	@echo "$(RED)Removing library and bitmap file...$(NORMAL)"
	rm -f $(NAME)
	rm -f cub3d.bmp
	rm -f ./utils/libft/libft.a
	@echo "$(GREEN)Successfully removed library and bitmap file!$(NORMAL)"

re: fclean all

%.o: %.c
	@echo "$(GREEN)Compiling:$(NORMAL)"
	$(GCC) $(INCLUDE_H) -c $<  -o $(<:.c=.o)
	@echo "$(GREEN)Successfully compiled!$(NORMAL)"

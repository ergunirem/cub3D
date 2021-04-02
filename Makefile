# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: icikrikc <icikrikc@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/10 14:12:56 by icikrikc      #+#    #+#                  #
#    Updated: 2021/03/08 17:56:56 by icikrikc      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# NAME = cub3D

# SOURCE_FILES =		main.c


# OBJ_FILES = $(SOURCE_FILES:.c=.o)
# # HEADER_FILE = ft_printf.h
# CFLAGS = -Wall -Wextra -Werror
# LIBFT = libft/libft.a
# MLX_LIB = minilibx

# all: $(NAME)

# $(NAME): $(OBJ_FILES)
# 	$(MAKE) -C libft
# 	$(MAKE) -C minilibx
# 	# $(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
# 	$(CC) -o $(NAME) $(OBJS) -L libft -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

# %.o: %.c #$(HEADER_FILE)
# 	@echo "$(GREEN)Compiling:$(NORMAL)"
# 	$(CC) $(CFLAGS) -Imlx -c $< -o $@

# # $(LIBRARY):
# # 	make bonus -C libft

# clean:
# 	@echo "$(RED)Removing all object files...$(NORMAL)"
# 	# make clean -C libft
# 	rm -f $(OBJ_FILES)
# 	@echo "$(GREEN)Succesfully removed all object files!$(NORMAL)"

# fclean: clean
# 	@echo "$(RED)Removing library...$(NORMAL)"
# 	# rm -f $(LIBRARY)
# 	rm -f $(NAME)
# 	@echo "$(GREEN)Successfully removed library!$(NORMAL)"

# re: fclean all

# .PHONY: all clean fclean re

GREEN = \033[38;5;2m
NORMAL = \033[38;5;255m
RED = \033[38;5;1m
BLUE = \033[38;5;4m

SRCS	=	utils/gnl/get_next_line.c utils/gnl/get_next_line_utils.c \
			main.c \
			parse.c parse_other.c parse_map.c\
			error.c \
			init.c \
			hooks.c \
			paint.c \
			draw.c ray-casting.c \
			move.c rotate.c \

OBJS	= $(SRCS:.c=.o)

NAME	= cub3D

GCC		= gcc

FLAGS	= -Wall -Wextra -Werror -fsanitize=address -g

INCLUDEH	= -I minilibx

MLX_DIR		=	minilibx_opengl

all:	$(NAME)

.PHONY:	clean fclean re bonus bench bclean

$(NAME):	$(OBJS)
	$(MAKE) bonus -C utils/libft
	$(MAKE) -C minilibx_opengl
	gcc $(FLAGS) -o $(NAME) $(OBJS) -L utils/libft -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

clean:
	@echo "$(RED)Removing all object files...$(NORMAL)"
	rm -f $(OBJS)
	make clean -C ./utils/libft
	@echo "$(GREEN)Succesfully removed all object files!$(NORMAL)"

fclean: clean
	@echo "$(RED)Removing library...$(NORMAL)"
	rm -f $(NAME)
	rm -f screenshot.bmp
	rm -f ./utils/libft/libft.a
	@echo "$(GREEN)Successfully removed library!$(NORMAL)"

re: fclean all

%.o: %.c
	@echo "$(GREEN)Compiling:$(NORMAL)"
	$(GCC) $(INCLUDEH) -c $<  -o $(<:.c=.o)
	@echo "$(GREEN)Successfully compiled!$(NORMAL)"

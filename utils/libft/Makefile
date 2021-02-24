NAME = libft.a

REG_SOURCE_FILES =		ft_atoi.c \
						ft_bzero.c \
						ft_calloc.c \
						ft_isalnum.c \
						ft_isalpha.c \
						ft_isascii.c \
						ft_isdigit.c \
						ft_isprint.c \
						ft_itoa.c \
						ft_memccpy.c \
						ft_memchr.c \
						ft_memcmp.c \
						ft_memcpy.c \
						ft_memmove.c \
						ft_memset.c \
						ft_putchar_fd.c \
						ft_putendl_fd.c \
						ft_putnbr_fd.c \
						ft_putstr_fd.c \
						ft_split.c \
						ft_strchr.c \
						ft_strdup.c \
						ft_strjoin.c \
						ft_strlcat.c \
						ft_strlcpy.c \
						ft_strlen.c \
						ft_strmapi.c \
						ft_strncmp.c \
						ft_strnstr.c \
						ft_strrchr.c \
						ft_strtrim.c \
						ft_substr.c \
						ft_toupper.c \
						ft_tolower.c \
						ft_xtoa.c \
						ft_iswhitespace.c \
						ft_putstr.c \
						ft_lstfree.c \

BONUS_SOURCE_FILES =	ft_lstnew.c \
						ft_lstadd_front.c \
						ft_lstsize.c \
						ft_lstlast.c \
						ft_lstadd_back.c \
						ft_lstdelone.c \
						ft_lstclear.c \
						ft_lstiter.c \
						ft_lstmap.c

CFLAGS = -Wall -Wextra -Werror

HEADER_FILES = libft.h

REG_OBJ_FILES = $(REG_SOURCE_FILES:.c=.o)

BONUS_OBJ_FILES = $(BONUS_SOURCE_FILES:.c=.o)

ifdef WITH_BONUS
OBJ_FILES = $(REG_OBJ_FILES) $(BONUS_OBJ_FILES)
else
OBJ_FILES = $(REG_OBJ_FILES)
endif

GREEN = \033[38;5;2m
NORMAL = \033[38;5;255m
RED = \033[38;5;1m
BLUE = \033[38;5;4m

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rc $@ $^

%.o: %.c $(HEADER_FILES)
	@echo "$(GREEN)Compiling:$(NORMAL)"
	$(CC) -c $(CFLAGS) -o $@ $<

bonus:
	$(MAKE) WITH_BONUS=1 all

clean:
	@echo "$(RED)Removing all object files...$(NORMAL)"
	rm -f $(REG_OBJ_FILES) $(BONUS_OBJ_FILES)
	@echo "$(GREEN)Succesfully removed all object files!"

fclean: clean
	@echo "$(RED)Removing libft.a...$(NORMAL)"
	rm -f $(NAME)
	@echo "$(GREEN)Successfully removed libft.a!"

re: fclean all

.PHONY: all clean fclean re

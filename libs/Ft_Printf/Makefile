MAKEFLAGS 			+= --no-print-directory
NAME = libftprintf.a

CC = @cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

SRC = ft_printf.c \
	ft_printf_utils.c

OBJ = $(SRC:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@$(AR) $(NAME) $(OBJ)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re.

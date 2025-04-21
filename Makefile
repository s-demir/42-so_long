MAKEFLAGS 			+= --no-print-directory
NAME = so_long

CC = @cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC		=		src/error_message.c							\
				src/graphics.c								\
				src/main.c									\
				src/map_create.c							\
				src/map_validation.c						\
				src/player_moves.c							\
				libs/GetNextLine/get_next_line.c			\
				libs/GetNextLine/get_next_line_utils.c

OBJ				= $(SRC:.c=.o)

LIBFT_PATH		= ./libs/Libft
LIBFT			= $(LIBFT_PATH)/libft.a

PRINTF_PATH		= ./libs/Ft_Printf
PRINTF			= $(PRINTF_PATH)/libftprintf.a

MINILIBX_PATH	= ./libs/minilibx-linux
MLX				= $(MINILIBX_PATH)/libmlx.a

LIBS			= -L$(MINILIBX_PATH) -lmlx -L/usr/X11/lib -lX11 -lXext

all:			$(NAME)

$(NAME):		$(OBJ) $(LIBFT) $(PRINTF) $(MLX)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(PRINTF) $(LIBS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_PATH) all

$(PRINTF):
	@make -C $(PRINTF_PATH) all

$(MLX):
	@make -C $(MINILIBX_PATH) all

clean:
	@make -C $(LIBFT_PATH) clean
	@make -C $(PRINTF_PATH) clean
	@make -C $(MINILIBX_PATH) clean
	@$(RM) $(OBJ)

fclean:		clean
	@make -C $(LIBFT_PATH) fclean
	@make -C $(PRINTF_PATH) fclean
	@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
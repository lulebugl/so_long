# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 16:00:50 by llebugle          #+#    #+#              #
#    Updated: 2024/11/08 19:47:12 by llebugle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# -----------------------------------Colors------------------------------------

RED		=\033[0;31m
GREEN	=\033[0;32m
YELLOW	=\033[1;33m
BLUE	=\033[0;34m
ORANGE	=\033[38;2;255;165;0m
RESET	=\033[0m

# ---------------------------------Compilation---------------------------------

NAME	= so_long
CC 		= cc
CFLAGS 	= -Werror -Wall -Wextra 
RM 		= rm -rf
OBJS 	= $(SRCS:.c=.o)

SRCS 	= so_long.c 		\
			events.c 		\
			map_parsing.c	\
			error.c			\

ifeq ($(shell uname), Linux)
	MLX_DIR = ./minilibx-linux
	MLX_PATH = minilibx-linux/libmlx.a
	MLX =  -L /usr/lib -lXext -lX11 -lm -lz 
	MLX_OBJ = -I/usr/include -Imlx_linux -O3
else
	MLX_DIR = ./mlx
	MLX_PATH = mlx/libmlx.a	
	MLX = -lmlx -Lmlx -framework OpenGl -framework AppKit
	MLX_OBJ = -Imlx -c
endif

# ---------------------------------Librairies----------------------------------

LIBFT = libft/libft.a
 
MLX_LIB = -L $(MLX_DIR) -lmlx


# -----------------------------------Rules-------------------------------------

all : $(NAME)

run: $(NAME)
	@printf "$(BLUE)Running so_long...$(RESET)\n"
	@./$(NAME) maps/example.ber

fullscreen: $(NAME)
	@printf "$(BLUE)Running so_long...$(RESET)\n"
	@./$(NAME) map.ber fullscreen

$(NAME) : $(OBJS)
	@make -C $(MLX_DIR)
	@make -C libft
	@$(CC) $(OBJS) $(LIBFT) $(CFLAGS) -g $(MLX_LIB) $(MLX) -o $(NAME)

%.o : %.c
	@$(CC) -o $@ -c $<

fclean : clean
	@make fclean -C libft
	@$(RM) so_long

clean :
	@make clean -C libft
	@$(RM) *.o

re : fclean all 

.PHONY: all clean fclean re run
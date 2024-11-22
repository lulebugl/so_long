# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 16:00:50 by llebugle          #+#    #+#              #
#    Updated: 2024/11/22 14:36:21 by llebugle         ###   ########.fr        #
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
NAME_BONUS	= so_long_bonus
CC 		= cc
CFLAGS 	= -Werror -Wall -Wextra -I includes
RM 		= rm -rf

OBJS_DIR = objs
OBJS_BONUS_DIR = objs_bonus
SRCS_DIR = srcs
SRCS_BONUS_DIR = srcs_bonus

SRCS 	= main.c 						\
			core/events.c 				\
			core/events_utils.c			\
			core/render.c				\
			core/textures.c				\
			core/game.c					\
			core/draw.c					\
			core/autotiling.c			\
			core/move_player.c			\
			core/utils.c				\
			core/error.c				\
			parsing/parsing.c			\
			parsing/matrix.c			\
			parsing/update_matrix.c		\
			parsing/map_utils.c			\
			parsing/map_solver.c		\
			parsing/map_init.c			\
			parsing/map_validation.c	\

SRCS_BONUS = $(SRCS) 

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(OBJS_BONUS_DIR)/, $(SRCS_BONUS:.c=.o))

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

bonus: $(NAME_BONUS)

$(NAME) : $(OBJS)
	@make -C $(MLX_DIR)
	@echo "$(GREEN)Building libft...$(RESET)"
	@make -s -C libft
	@$(CC) $(OBJS) $(LIBFT) $(CFLAGS) -g $(MLX_LIB) $(MLX) -o $(NAME)

$(NAME_BONUS) : $(OBJS_BONUS)
	@make -C $(MLX_DIR)
	@echo "$(GREEN)Building libft...$(RESET)"
	@make -s -C libft
	@$(CC) $(OBJS_BONUS) $(LIBFT) $(CFLAGS) -g $(MLX_LIB) $(MLX) -o $(NAME_BONUS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
#@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@$(CC) $(INC) -c $< -o $@

$(OBJS_BONUS_DIR)/%.o: $(SRCS_BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
#@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@$(CC) -c $< -o $@

fclean : clean
	@make fclean -C libft
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)

clean :
	@make clean -C libft
	@$(RM) -r $(OBJS_DIR)
	@$(RM) -r $(OBJS_BONUS_DIR)
	@$(RM) srcs/*.o

re : fclean all

.PHONY: all clean fclean re run bonus
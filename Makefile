# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 16:00:50 by llebugle          #+#    #+#              #
#    Updated: 2024/11/11 22:30:08 by llebugle         ###   ########.fr        #
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
CFLAGS 	= -Werror -Wall -Wextra -I includes
RM 		= rm -rf
OBJS 	= $(SRCS:.c=.o)

SRCS 	= srcs/so_long.c 			\
			srcs/events.c 			\
			srcs/map_parsing.c		\
			srcs/parsing.c			\
			srcs/map_validation.c	\
			srcs/error.c			\
			srcs/solve.c			\
			srcs/utils.c

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
	@make -s -C libft
	@$(CC) $(OBJS) $(LIBFT) $(CFLAGS) -g $(MLX_LIB) $(MLX) -o $(NAME)

%.o : %.c
	@$(CC) -o $@ -c $<

fclean : clean clean_test
	@make fclean -C libft
	@$(RM) so_long

clean : clean_test
	@make clean -C libft
	@$(RM) srcs/*.o

re : fclean all

# -----------------------------------Tests-------------------------------------

TEST_DIR	= tests
TEST_SRCS	= $(TEST_DIR)/test_parsing.c	\
		$(TEST_DIR)/test_main.c			 	\
		$(TEST_DIR)/test_reader.c

TEST_OBJS	= $(TEST_SRCS:.c=.o)
TEST_NAME	= test_runner

# Add test-specific flags
TEST_FLAGS	= -g -I./Unity/src

# Rules for testing
test: $(TEST_NAME)
	@printf "$(BLUE)Running tests...$(RESET)\n"
	@valgrind ./$(TEST_NAME)

$(TEST_NAME): $(TEST_OBJS) $(filter-out srcs/so_long.o, $(OBJS))
	@make -C $(MLX_DIR)
	@make -s -C libft
	@$(CC) $(TEST_OBJS) $(filter-out srcs/so_long.o, $(OBJS)) $(LIBFT) \
		$(TEST_FLAGS) $(MLX_LIB) $(MLX) -o $(TEST_NAME)

$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	@$(CC) $(CFLAGS) $(TEST_FLAGS) -c $< -o $@

clean_test:
	@$(RM) $(TEST_OBJS) $(TEST_NAME)

.PHONY: all clean fclean re run test clean_test
#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 09:46:53 by zerrino           #+#    #+#              #
#    Updated: 2024/07/25 01:13:34 by alexafer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

X = 10
Y = 10

CC = gcc
CFLAGS =   -Wall -Wextra -Werror -g -fsanitize=address
LFLAGS = -framework OpenGL -framework AppKit -lz

SRC_DIR = srcs
OBJ_DIR = objs
INC_DIR = includes
MINI_DIR = minilibx
LIBFT_DIR = libft

SRC_FILES = main.c get_next_line.c get_next_line_utils.c parsing.c utils.c utils1.c utils2.c utils3.c utils4.c draw_wall.c\
	render_scene.c render_scene1.c key_pressing.c player_finder.c animated.c opening.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(MINI_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft -L$(MINI_DIR) -lmlx $(LFLAGS)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MINI_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpolizzi <lpolizzi@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 13:56:58 by lpolizzi          #+#    #+#              #
#    Updated: 2024/10/21 23:35:28 by lpolizzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC       = gcc
CFLAGS   = -Wall -Wextra -Werror

# Directories
SRC_DIR  = srcs
OBJ_DIR  = objs
LIBFT_DIR = libft
MLX_DIR  = minilibx-linux

# Libraries
LIBFT    = $(LIBFT_DIR)/libft.a
MLX      = $(MLX_DIR)/libmlx_Linux.a
LIBS     = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux -lm -lX11 -lXext

# Includes
INCLUDES = -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR)

# Source files and object files
SRCS     = $(SRC_DIR)/fractol.c \
           $(SRC_DIR)/init.c \
           $(SRC_DIR)/init_helper.c \
           $(SRC_DIR)/render.c \
           $(SRC_DIR)/render_utils.c \
           $(SRC_DIR)/color.c \
           $(SRC_DIR)/color_utils.c \
           $(SRC_DIR)/event_handling.c \
           $(SRC_DIR)/help_msg.c \
           $(SRC_DIR)/error_and_exit.c

OBJS     = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output executable
NAME     = fractol

# Rules
all: $(LIBFT) $(MLX) $(NAME)

# Compile libft if not already compiled
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compile MiniLibX if not already compiled
$(MLX):
	$(MAKE) -C $(MLX_DIR)

# Create object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link the executable
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

# Clean object files
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

# Clean object files and executable
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

# Rebuild
re: fclean all

.PHONY: all clean fclean re

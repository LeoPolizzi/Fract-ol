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
CC       = cc
CFLAGS   = -Wall -Wextra -Werror -Ofast -march=native -flto

# Directories
SRC_DIR  = srcs
BONUS_DIR = bonus_srcs
OBJ_DIR  = objs
LIBFT_DIR = libft
MLX_DIR  = .minilibx-linux

# Libraries
LIBFT    = $(LIBFT_DIR)/libft.a
MLX      = $(MLX_DIR)/libmlx_Linux.a
LIBS     = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux -lm -lX11 -lXext

# Includes
INCLUDES = -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR)
BONUS_INCLUDES = -Ibonus_include -I$(MLX_DIR) -I$(LIBFT_DIR)

# Source files and object files
SRCS     = $(SRC_DIR)/fractol.c \
           $(SRC_DIR)/init.c \
           $(SRC_DIR)/init_helper.c \
           $(SRC_DIR)/render.c \
           $(SRC_DIR)/color.c \
           $(SRC_DIR)/event_handling.c \
           $(SRC_DIR)/help_msg.c \
           $(SRC_DIR)/error_and_exit.c

BONUS_SRCS = $(BONUS_DIR)/fractol_bonus.c \
           $(BONUS_DIR)/init_bonus.c \
           $(BONUS_DIR)/init_helper_bonus.c \
           $(BONUS_DIR)/render_bonus.c \
           $(BONUS_DIR)/color_bonus.c \
           $(BONUS_DIR)/event_handling_bonus.c \
           $(BONUS_DIR)/help_msg_bonus.c \
           $(BONUS_DIR)/error_and_exit_bonus.c

OBJS     = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output executable
NAME     = fractol
BONUS_NAME = fractol_bonus

# Rules
all: $(LIBFT) $(MLX) $(NAME)

# Make bonus version
bonus: $(LIBFT) $(MLX) $(BONUS_NAME)

# Compile libft if not already compiled
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null

# Compile MiniLibX if not already compiled
$(MLX):
	@$(MAKE) -C $(MLX_DIR) > /dev/null

# Create object directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(BONUS_INCLUDES) -c $< -o $@

# Link the executable
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "Executable compiled."

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBS) -o $(BONUS_NAME)
	@echo "Bonus version compiled."

# Clean object files
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null
	@rm -rf $(OBJ_DIR)
	@echo "Clean done."

# Clean object files and executable
fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null
	@rm -f $(NAME) $(BONUS_NAME)
	@echo "Full clean done."

# Rebuild
re: fclean all

.PHONY: all clean fclean re

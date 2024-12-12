# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: natallia <natallia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 13:03:26 by nkhamich          #+#    #+#              #
#    Updated: 2024/12/12 14:03:03 by natallia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
SRC			= pipex.c pipex_utils.c
SRC_BONUS	= bonus/main_bonus.c bonus/files_bonus.c \
				bonus/children_bonus.c bonus/utils_bonus.c
OBJ_DIR		= obj
OBJ			= $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS	= $(SRC_BONUS:%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "Object directory created for $(NAME)."

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(NAME) executable created successfully."

$(LIBFT):
	@make -C $(LIBFT_PATH) all

bonus: $(OBJ_BONUS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) -o $(NAME)
	@echo "$(NAME) bonus executable created successfully."

clean:
	@make -C $(LIBFT_PATH) clean
	@rm -rf $(OBJ_DIR)
	@echo "Object files cleaned for $(NAME)."

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -rf $(NAME)
	@echo "Executable fully cleaned."

re: fclean all

.PHONY: all bonus clean fclean re libft

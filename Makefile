# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mianni <mianni@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/11 11:43:29 by mianni            #+#    #+#              #
#    Updated: 2025/02/18 19:17:33 by mianni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Couleurs pour l'affichage
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
NC=\033[0m # No Color

# Variables
NAME = minishell
INCLUDES = -I minishell.h
SRC_DIR = ./srcs
OBJ_DIR = ./obj

SRC = $(SRC_DIR)/minishell.c \
      $(SRC_DIR)/tokenisation/tokenisation.c \
      $(SRC_DIR)/tokenisation/tokenisation1.c \
      $(SRC_DIR)/utils/check_token.c \
	  $(SRC_DIR)/utils/check_token2.c \
	  $(SRC_DIR)/utils/check_token3.c \
	  $(SRC_DIR)/utils/check_token4.c \
      $(SRC_DIR)/utils/utils1.c \
      $(SRC_DIR)/utils/utils2.c \
      $(SRC_DIR)/utils/utils3.c \
	  $(SRC_DIR)/utils/utils4.c \
	  $(SRC_DIR)/utils/utils5.c \
	  $(SRC_DIR)/utils/utils6.c \
	  $(SRC_DIR)/utils/utils7.c \
	  $(SRC_DIR)/utils/utils8.c \
      $(SRC_DIR)/parsing/parsing.c \
      $(SRC_DIR)/parsing/parsing_utils.c \
      $(SRC_DIR)/ast/ast_generator.c \
	  $(SRC_DIR)/ast/ast_utils.c \
      $(SRC_DIR)/error/error.c \
	  $(SRC_DIR)/design/design.c  \
	  $(SRC_DIR)/env/env_list.c \
	  $(SRC_DIR)/exec/open_files.c \
	  $(SRC_DIR)/exec/get_path.c \
	  $(SRC_DIR)/exec/exec.c\
	  $(SRC_DIR)/exec/exec2.c\
	  $(SRC_DIR)/exec/exec3.c\
	  $(SRC_DIR)/builtins/cd.c \
	  $(SRC_DIR)/builtins/pwd.c \
	  $(SRC_DIR)/builtins/echo.c \
	  $(SRC_DIR)/builtins/export.c \
	  $(SRC_DIR)/builtins/export.c \
	  $(SRC_DIR)/builtins/exit.c \
	  $(SRC_DIR)/builtins/env.c \
	  $(SRC_DIR)/builtins/unset.c \
	  $(SRC_DIR)/signal/signal.c \
	  $(SRC_DIR)/wildcards/wildcards.c \
	  $(SRC_DIR)/wildcards/wildcards_utils.c \
	  $(SRC_DIR)/wildcards/wildcards_utils1.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CC = cc
CFLAGS = -g3
LIBFT = ./libft/libft.a
LIBFT_PATH = ./libft

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) bonus -C $(LIBFT_PATH)

libft_clean:
	@$(MAKE) clean -C $(LIBFT_PATH) > /dev/null 2>&1

libft_fclean:
	@$(MAKE) fclean -C $(LIBFT_PATH) > /dev/null 2>&1

$(NAME): $(OBJ) $(LIBFT)
	@echo "${YELLOW}Compiling...${NC}"
	@$(CC) $(CFLAGS) $^ -o $@ -L$(LIBFT_PATH) -lft -lreadline -lncurses
	@echo "${GREEN}Minishell compiled successfully!${NC}"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean: libft_clean
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)

fclean: libft_fclean clean
	@rm -f $(NAME)
	@echo "${RED}All objs and executables cleaned successfully!${NC}"

re: fclean all

.PHONY: all clean fclean re LIBFT libft_clean libft_fclean


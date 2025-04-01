##
## EPITECH PROJECT, 2024
## c_proj_template
## File description:
## Makefile
##

# Colors
BOLD=\033[1m
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
NC=\033[0m # No Color

MAKEFLAGS += --no-print-directory

.PHONY: all clean fclean re debug

# Directories
LIB_DIR = lib
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

# Files
LIB	=	$(LIB_DIR)/libmy.a

SRC	=	$(SRC_DIR)/main.c 		\
		$(SRC_DIR)/parsing.c 	\
		$(SRC_DIR)/alloc_wrap.c \
		$(SRC_DIR)/link_node.c 	\
		$(SRC_DIR)/my_realloc.c \
OBJ =	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
NAME	=	amazed

# Compiler
CC = gcc
CFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -L$(LIB_DIR) -lmy

all: $(LIB) $(NAME)

$(LIB):
	@$(MAKE) -C $(LIB_DIR)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) -L$(LIB_DIR) -lmy
	@echo -e "$(GREEN)[PROGRAM] $(BLUE)Program compiled$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo -e "$(GREEN)[PROGRAM]$(NC)Compiling $<$(NC)"
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@echo -e "$(GREEN)[PROGRAM] $(BLUE)Clean$(NC)"
	@$(MAKE) -C $(LIB_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(LIB)
	@echo -e "$(YELLOW)[LIBRARY] $(BLUE)Full clean$(NC)"
	@rm -f $(NAME)
	@echo -e "$(GREEN)[PROGRAM] $(BLUE)Full clean$(NC)"

re: fclean all

debug: CFLAGS += -g
debug: all

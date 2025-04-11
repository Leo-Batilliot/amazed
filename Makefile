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

SRC	=	$(SRC_DIR)/main.c \
		$(SRC_DIR)/utils/mini_printf.c \
		$(SRC_DIR)/utils/utils.c \
		$(SRC_DIR)/utils/lists.c \
		$(SRC_DIR)/utils/free.c \
		$(SRC_DIR)/utils/free_list.c \
		$(SRC_DIR)/utils/array_len.c \
		$(SRC_DIR)/parsing/parsing.c \
		$(SRC_DIR)/parsing/links.c \
		$(SRC_DIR)/parsing/rooms.c \
		$(SRC_DIR)/parsing/robots.c \
		$(SRC_DIR)/algo/algo_main.c \
		$(SRC_DIR)/algo/calculations.c \
		$(SRC_DIR)/algo/init.c \
		$(SRC_DIR)/algo/free.c \

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

BONUS_SRC_DIR = bonus
BONUS_OBJ_DIR = obj_bonus

BONUS_SRC = $(BONUS_SRC_DIR)/$(SRC_DIR)/main.c 						\
			$(BONUS_SRC_DIR)/lib/linked_list.c						\
			$(BONUS_SRC_DIR)/lib/split_string.c 					\
			$(BONUS_SRC_DIR)/lib/my_strncpy.c 						\
			$(BONUS_SRC_DIR)/lib/free.c 							\
			$(BONUS_SRC_DIR)/$(SRC_DIR)/utils/buttons_draw.c 		\
			$(BONUS_SRC_DIR)/$(SRC_DIR)/utils/buttons_free.c 		\
			$(BONUS_SRC_DIR)/$(SRC_DIR)/utils/buttons_init.c 		\
			$(BONUS_SRC_DIR)/$(SRC_DIR)/utils/buttons_state.c 		\
			$(BONUS_SRC_DIR)/$(SRC_DIR)/utils/arrays.c 				\
			$(BONUS_SRC_DIR)/$(SRC_DIR)/sim/init_sim.c 				\
			$(BONUS_SRC_DIR)/$(SRC_DIR)/sim/free_sim.c 				\
           	$(BONUS_SRC_DIR)/$(SRC_DIR)/sim/sim_render.c			\
			$(BONUS_SRC_DIR)/$(SRC_DIR)/sim/event.c 				\
			$(BONUS_SRC_DIR)/$(SRC_DIR)/sim/parsing.c				\
			$(BONUS_SRC_DIR)/$(SRC_DIR)/sim/main_loop.c				\
			$(BONUS_SRC_DIR)/$(SRC_DIR)/sim/sim_main.c 				\
			$(BONUS_SRC_DIR)/$(SRC_DIR)/main_menu/menu_main.c 		\
			$(BONUS_SRC_DIR)/$(SRC_DIR)/main_menu/menu_events.c 	\
			$(BONUS_SRC_DIR)/$(SRC_DIR)/main_menu/init_menu.c 		\
			$(BONUS_SRC_DIR)/$(SRC_DIR)/main_menu/free_menu.c 		\


BONUS_OBJ = $(BONUS_SRC:$(BONUS_SRC_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)
BONUS_NAME = amazed_bonus

CSFMLFLAGS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
BONUS_INCLUDE_DIR = bonus/include

bonus: CFLAGS = -I$(BONUS_INCLUDE_DIR)  $(CSFMLFLAGS)
bonus: CFLAGS += -Wall -Wextra -L$(LIB_DIR) -lmy -lm
bonus: $(BONUS_OBJ)
	@$(CC) -o $(BONUS_NAME) $(BONUS_OBJ) $(CFLAGS)
	@echo -e "$(GREEN)[BONUS] $(BLUE)Bonus program compiled$(NC)"

$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo -e "$(GREEN)[BONUS]$(NC)Compiling $<$(NC)"
	@$(CC) -c $< -o $@ $(CFLAGS)

clean_bonus:
	@rm -rf $(BONUS_OBJ_DIR)
	@echo -e "$(GREEN)[BONUS] $(BLUE)Bonus clean$(NC)"

fclean_bonus: clean_bonus
	@rm -f $(BONUS_NAME)
	@echo -e "$(YELLOW)[BONUS] $(BLUE)Full bonus clean$(NC)"

re_bonus: fclean_bonus bonus

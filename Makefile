SHELL :=  /bin/bash

NAME := philo
SRC_DIR := src
OBJ_DIR := obj
HEAD := ./include/philo.h
SOURCES := $(SRC_DIR)/activities.c $(SRC_DIR)/main.c $(SRC_DIR)/monitoring.c \
			$(SRC_DIR)/parser.c $(SRC_DIR)/philo_maker.c $(SRC_DIR)/simulation.c \
			$(SRC_DIR)/utils.c $(SRC_DIR)/utils2.c $(SRC_DIR)/utils3.c $(SRC_DIR)/mutex.c \

OBJECTS := $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SOURCES:.c=.o))
CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread -g3 -fsanitize=address

GREEN = \x1b[32;01m
RED = \x1b[31;01m
YELLOW = \033[33;1m
BOLD = \033[1m
RESET = \x1b[0m
RM = /bin/rm -f

all: $(NAME)

$(NAME): $(HEAD) $(OBJ_DIR) $(OBJECTS) $(SOURCES)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@printf "$(GREEN) $(BOLD)======= Created program $(NAME) ======= $(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "Compiling... $(notdir $<)\n"

clean:
	@$(RM) -rf $(OBJ_DIR)
	@printf "$(RED) $(BOLD) Deleting objects... $(RESET)\n"

fclean: clean
	@$(RM) -rf $(NAME)
	@printf "$(RED) $(BOLD) Deleting $(NAME)... $(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
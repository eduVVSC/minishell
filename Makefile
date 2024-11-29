CC = cc -g
NAME = minishell

#FLAGS
FLAGS = -I$(INC_DIR) -I$(LIB_DIR)

# Color variables
RED = \033[0;31m
GRN = \033[0;32m
YEL = \033[0;33m
BLU = \033[0;34m
MAG = \033[0;35m
CYN = \033[0;36m
WHT = \033[0;37m
RES = \033[0m

# PATHS
INC_DIR = include/
LIB_DIR = libft/
SRC_DIR = src/
OBJ_DIR = obj/

# FILES
LIBFT = $(LIB_DIR)libft.a
MAIN_FILE = main.c

SRC_FILES := $(shell find $(SRC_DIR) -name '*.c' ! -name 'main.c')

OBJ_FILES := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_FILES))

#PHONY TARGETS
.PHONY: all clean fclean re

#RULES
all: ${NAME}

${NAME}: ${LIBFT} ${MAIN_FILE} $(OBJ_FILES) | $(OBJ_DIR)
	@${CC} ${FLAGS} ${MAIN_FILE} -lreadline $(OBJ_FILES) $(LIBFT) -o $(NAME)
	@echo "$(GRN)[ ${NAME} ] compiled successfully.$(RES)"

${LIBFT}:
	@make --silent -C $(LIB_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
		@rm -f ${OBJ}
		@rm -f $(LIB_DIR)/*.o
		@echo "$(WHT)Clean command executed.$(RES)"

fclean: clean
		@rm -f ${NAME}
		@rm -f ${LIBFT}

re: fclean all

CC = cc
NAME = minishell

#FLAGS
FLAGS = -g -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIB_DIR)

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

SRC_FILES := src/heredoc/heredoc.c src/heredoc/create_heredoc.c src/heredoc/read_heredocs.c src/heredoc/heredoc_utils.c \
     		 src/heredoc/expansion_heredoc.c src/tree/build/tree_builder.c src/tree/build/build_cmd_array.c src/tree/build/free_tree.c \
     		 src/tree/build/build_cmd_list.c src/tree/build/build_cmd_utils.c src/tree/execute/execute_errors.c src/tree/execute/exec_cmds.c \
     		 src/tree/execute/exec_tree_utils.c src/tree/execute/exec_tree.c src/tree/execute/handle_sig_builtins.c src/errors/errors.c \
     		 src/expansions/handle_expansions.c src/expansions/utils_expansions.c src/redirections/redirections.c src/redirections/clean_redirs.c \
     		 src/redirections/redir_utils.c src/builtins/filter_commands.c src/builtins/commands/exit.c src/builtins/commands/export.c \
     		 src/builtins/commands/utils_builtins.c src/builtins/commands/util_env_var.c src/builtins/commands/unset.c src/builtins/commands/cd.c \
     		 src/builtins/commands/pwd.c src/builtins/commands/util_env.c src/builtins/commands/echo.c src/builtins/commands/cd_utils.c \
     		 src/builtins/commands/export_utils.c src/builtins/commands/env.c src/tokens/get_info.c src/tokens/tokenization.c \
     		 src/tokens/token_utils.c src/setup/setting_shell.c src/setup/setting_env.c src/signals/handler.c \
     		 src/utils/redirs_in_parent.c src/utils/clean.c src/utils/clean_funtions.c src/utils/utils.c \
     		 src/utils/count_words.c src/syntax/check_invalid_chars.c src/syntax/syntax_utils.c src/syntax/handle_quotes.c \
     		 src/syntax/syntax_check.c 

OBJ_FILES := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_FILES))

#PHONY TARGETS
.PHONY: all clean fclean re

#RULES
all: ${NAME}

${NAME}: ${LIBFT} ${MAIN_FILE} $(OBJ_FILES) | $(OBJ_DIR)
	@${CC} ${FLAGS} ${MAIN_FILE} $(OBJ_FILES) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(GRN)[ ${NAME} ] compiled successfully.$(RES)"

${LIBFT}:
	@make --silent -C $(LIB_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
		@rm -rf ${OBJ_DIR}
		@make clean --silent -C $(LIB_DIR)
		@echo "$(WHT)Clean command executed.$(RES)"

fclean: clean
		@rm -f ${NAME}
		@rm -f ${LIBFT}

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=sup_readline.supp --track-origins=yes --track-fds=yes ./minishell


re: fclean all

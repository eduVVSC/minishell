/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:12:10 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/28 11:46:40 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0

# define GENERAL 0
# define SINGLE_QUO 1
# define DOUBLE_QUO 2
# define EXPANDED 3

# define PIPE 1
# define INFILE 2
# define TRU_OUTFILE 3
# define APP_OUTFILE 4
# define HEREDOC 5
# define EXPANSION 6
# define SPACE 7

# define READ 0
# define WRITE 1

// DEFINE ERRORS

# define OPEN_PIPE_ERROR -1
# define OPEN_QUOTE_ERROR -2
# define INVALID_CHAR_ERROR -3
# define UNEXPECTED_TOKEN -4

# include <stdio.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/libft.h"

typedef struct s_shell
{
	struct s_env		*env;
	struct s_tokens		*tokens;
	struct s_tree_node	*tree;
	struct s_cmds		*cmd_list;
	struct s_heredock	*heredock;
	char				*dir_now;
}			t_shell;

typedef struct s_env
{
	char			*var_name;
	char			*operant;
	char			*var_value;
	int				printed;
	int				behaviour;
	struct s_env	*next;
}				t_env;

typedef struct s_cmds
{
	struct s_tokens	*token_list;
	struct s_cmds	*next;
}				t_cmds;

typedef struct s_tree_node
{
	struct s_tokens		*content;
	int					last_heredoc_fd;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}					t_tree_node;

typedef struct s_tokens
{
	char			*token;
	int				type;
	int				state;
	int				index;
	struct s_tokens	*next;
}				t_tokens;

typedef struct s_heredock
{
	int					state;
	char				*key;
	char				*fullinput_until_key;
	struct s_heredock	*next;
}				t_heredock;

extern int	g_sig_sign;
// =====================functions====================== //

// ===== creating shell =====//
void		create_env(t_shell *shell, char **envp);
t_env		*create_env_no_envp(void);
t_env		*create_env_envp(char **envp);
t_shell		*setting_shell(int ac, char **av, char **envp);

// ===== env utils =====//

t_env		*creating_env_var(char *full_declaration);
t_env		*creating_env_var_w_no_value(char *full_declaration);
int			count_env(t_env *env);
char		*get_env_var_value(t_env *env, char *var_searching);
void		zero_all_env(t_env *env);
void		adding_var_in_list(t_env **env, t_env *node);
void		add_new_variable(t_env *env, t_env *new_variable);
void		free_n_add_exit_status(t_shell *shell, char *new_value);
void		refresh_var_value(t_env *env,
				t_env *var_with_new_value, int behavior);

// ===== cleaning =====//
int			clean_all_and_close(t_shell *shell);
int			clean_and_terminate_with_status(t_shell *shell, int status);
int			clean_and_terminate(t_shell *shell);
void		free_env_node(t_env *node);
void		free_env(t_env *env);
void		free_cmd_list(t_cmds *cmds);
void		free_tree(t_tree_node *head);
void		free_tokens(t_tokens *tokens);
void		clean_next_round(t_shell *shell);
void		clean_fds(t_tree_node *node);
void		close_fds(int *fd);

// =============tokens=============== //

t_tokens	*get_tokens(t_shell *shell, char *input);
int			get_token_state(char *str);
int			get_token_type(char *str);
int			count_spaces(char *str);
int			is_quote(char c);
int			is_redir(char c);
int			are_there_more_tokens(char *input);
char		*clean_tkn_quotes(char *str);
void		set_quote_state(char c, int *quote_state);
void		create_space_token(t_tokens *tokens);
void		initializing_values(int *i, int *j, int *close_quote);

// =============tree=============== //

t_tokens	*copy_token_node(t_tokens *token);
t_tokens	*ft_lstlast_a(t_tokens *lst);
t_cmds		*build_cmd_list(t_tokens *tokens);
void		pipe_error(t_shell *shell);
void		fork_error(t_shell *shell);
void		print_cmds(char **cmds);
char		*make_tree(t_shell *shell);
void		exec_tree(t_shell *shell, t_tree_node *node);
void		exec_cmd(t_shell *shell, t_tokens *node_content);
char		**build_cmd(t_tokens **tokens);
char		*find_path(char *cmd, t_env *envp);
void		ft_lstadd_back_a(t_tokens **lst, t_tokens *new);
// Exec Tree Utils
int			is_heredoc_command(char **cmd);
int			get_matrix_len(char **matrix);
int			is_redir_token(t_tokens *tokens);
int			handle_heredoc_exec(t_shell *shell, t_tree_node *node);
void		check_if_builtin(char **cmd, char *envp);
int			has_redirection(t_tokens *tokens);
int			open_file(char *file_name, int flag);
int			execute_builtin_in_parent(t_shell *shell);
int			exec_builtin_especial_cases(t_shell *shell,
				t_tokens *node_content, int fd1, int fd2);

// ============= redirections =============== //

int			is_infile(char *str);
int			is_outfile(char *str);
void		dup_from_input(int fd);
void		dup_to_output(int fd);
void		clean_redirs(t_tokens *tokens);
void		handle_redirections(t_shell *shell,
				t_tokens *tokens, int last_heredoc_fd);

// ================== built-ins ==================== //

//=========== pwd command ===========//
int			do_pwd(char **command);
void		start_pwd(t_env *temp);
void		start_old_pwd(t_env *temp, char *old_pwd_value);
int			is_builtin( t_shell *shell, char **command);

//=========== echo command ===========//

int			do_echo(char **command);

//=========== unset command ===========//

int			do_unset(t_env *env, char **command);
int			on_first_node(t_env **env);
int			remove_env_var(t_env *env, char *env_to_remove);
void		clean_first_node(t_env *node);
void		clean_env_node_attributes(t_env *node);

//=========== env command ============//

int			do_env(char **command, t_env *env);
int			handle_env_error(char *command);
void		print_env(t_env *env);

//=========== export command ==========//

t_env		*creating_var(char *declaration);
int			do_export(t_env **env, char **command);
int			check_var_name(char *var_name);
int			check_if_have_equal_sign(char *declaration);
int			search_in_env(t_env *env, char *searching_var);
char		*only_name(char *str);
char		*only_value(char *str);
char		*only_operant(char *str);
void		print_sorted(t_env *env);
void		print_env_export(t_env *node);

//========= cd command ==========//

int			do_cd(t_shell *s_heredock, char **command);
int			cd_no_args(t_env *env);
int			cd_args(t_env *env, char **command);
int			check_file_type(char *dir_path);
int			handle_cd_error(char **command);
int			cd_opitionals(t_env *env, char **command);
void		refresh_pwd_oldpwd(t_shell *shell, char *old_pwd);

//========= exit command ==========//

int			get_exit_code(char **cmd);
int			has_only_nrs(char *arg);
void		do_exit(t_shell *shell, char **cmd);

// ===builtins utils=== //

char		**transfrom_env_to_array(t_env *env);
char		*join_str_char(char *s1, char s2);
char		*ft_strjoin_free_s1(char *s1, char *s2);
int			get_height(char **array);
int			env_height(t_env *env);
int			ft_strcmp(char *str1, char *str2);
int			check_exist_optionals(char **command);

// =============heredoc=============== //

t_heredock	*create_heredoc(t_tree_node *node);
t_heredock	*create_heredoc_node(t_tokens *key);
t_heredock	*free_heredock(t_heredock *heredock);
t_heredock	*create_heredoc_body(t_tree_node *node, int i);

int			search_exp_heredoc(char *str);
int			creating_temp_file(char *write);
int			doing_key(t_heredock *heredock);
int			count_heredocs(t_tokens *tokens);
char		*expand_heredoc(t_env *env, char *str);
char		*ft_strjoin_w_new_line(char *s1, char *s2);
void		process_heredocs(t_shell *shell);
void		handle_heredoc(t_shell *shell, t_tokens *redir, int fd);
void		doing_heredock(t_shell *shell, t_heredock *heredock, int fd);

// =============handlers=============== //

void		cntrl_c(void);
void		cntrl_backslash(void);
void		handle_commands(t_shell *shell);
void		signal_handler(int signum, siginfo_t *info, void *context);

// ============Syntax============== //

int			is_normal_char(char c);
int			is_forbidden_char(char c);
int			has_double_pipe(char *input, int i);
int			check_syntax(t_shell *shell, char *input);
int			check_invalid_chars(char *input, int i);
void		print_syntax_error(int error_num);

// ============Expansion============== //

int			check_expand(char *str);
char		*takeoff_quotes(char *str);
char		*var_name(char *str, int start);
char		*handle_expension(t_env *env, char *str);
char		*re_wrinting_string(char *str,
				char *expand_value, int where_to_change, int var_len);

void		expand_token(t_env *env, t_tokens *token);

// ============General Utils============== //

int			is_separator(char c);
int			handle_quotes(const char *str, int i, char quote_type);
int			count_words(char *str);

// =============== Syntax ================= //

int			check_open_quotes(const char *str);

#endif

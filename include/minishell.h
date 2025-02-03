/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:12:10 by dioferre          #+#    #+#             */
/*   Updated: 2025/02/03 17:18:01 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//# define TMPFILE "~/../../tmp/.minishellTempFIle"
# define TMPFILE "./minishellTempFIle"
# define true 1
# define false 0
# define variable 1
# define value 0

# define string 0
# define infile 2
# define outfile 3
# define heredoc 4
# define expansion 5

# define general 0
# define single_quo 1
# define double_quo 2
# define expanded 3

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

# include <stdio.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/libft.h"


typedef struct s_shell
{
	struct s_env		*env;
	struct s_tokens		*tokens;
	struct s_tree_node	*tree;
	struct s_cmds		*cmd_list;
	char				*dir_now; // thi will be pwd with an $ in the end
	struct s_heredock	*heredock;
	//t_tree_node	*tree;
	//char		*message;?
}			t_shell;

typedef struct s_env
{
	char			*var_name;
	char			*operant;
	char			*var_value;
	int				printed; // to be used on the export with no args
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
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}					t_tree_node;

typedef struct s_tokens
{
	char			*token;
	int				type; // 0 str, 1 pipe, 2 & ,3 infile, 4 outfile, 5 heredoc, 6 expansion.
	int				state; //0 general, 1 single quote, 2 double quote, 3 expanded;
	int				index;
	struct	s_tokens	*next;
}				t_tokens;

typedef struct s_heredock
{
	char				*key;
	int 				state;// add it in the conversion from the tokens!!!
	char				*fullinput_until_key;
	struct s_heredock	*next;
}				t_heredock;

// =====================functions====================== //

// ===== creating shell =====//
t_env	*create_env_no_envp();
t_env	*create_env_envp(char **envp);
void	*create_env(t_shell *shell, char **envp);
t_shell	*setting_shell(int ac, char **av, char **envp);


// ===== env utils =====//

int		count_env(t_env *env);
void	zero_all_env(t_env *env);
t_env	*creating_env_var(char *full_declaration);
void	adding_var_in_list(t_env **env, t_env *node);
void	add_new_variable(t_env *env ,t_env *new_variable);
char	*get_env_var_value(t_env *env, char *var_searching);
t_env	*creating_env_var_w_no_value(char *full_declaration);
void	refresh_var_value(t_env *env, t_env *var_with_new_value, int behavior);


// ===== cleaning =====//
void	free_env_node(t_env *node);
void	free_env(t_env *env);
void	free_cmd_list(t_cmds *cmds);
void	free_tree(t_tree_node *head);
void	free_tokens(t_tokens *tokens);
void	clean_next_round(t_shell *shell);
int		clean_all_and_close(t_shell *shell);
int		clean_and_terminate_with_status(t_shell *shell, int status);
int		clean_and_terminate(t_shell *shell);
void	free_tokens(t_tokens *tokens);


// ===== organize later =====//

void	start_pwd(t_env *temp);
void	start_old_pwd(t_env *temp, char *old_pwd_value);
void	cleanedHandler(int signum, siginfo_t *info, void *context);
char		**transfrom_env_to_array(t_env *env);
int			env_height(t_env *env);
int			check_input(t_shell *shell, char *input);
t_tokens	*get_tokens(t_shell *shell, char *input);
int			is_separator(char c);
int			get_token_state(char *str);
int			get_token_type(char *str);
void		print_tokens(t_tokens *tokens);
void		giving_value_to_str(char *str, char *cmd, int strlen, int index_start);
int			handle_quotes(const char *str, int i, char quote_type);
int			word_count(char *str);
char		**build_cmd(t_tokens **tokens);
t_cmds		*build_cmd_list(t_tokens *tokens);
void		print_cmds(char **cmds);
int			is_builtin( t_shell *shell, char **command);
void		print_individual_tkn(t_tokens *token);
int			check_open_brackets(const char *str);
int			check_open_quotes(const char *str);
void		strjoin_and_replace(char **s1, char *s2);
int			count_words(char *str);
int			is_pipe_node(char **content);
int			get_matrix_len(char **matrix);
int			is_redir_token(t_tokens *tokens);
void		file_error(t_shell *shell);
// TO ORGANIZE :p

// =============tokens=============== //

void	create_space_token(t_tokens *tokens);
char	*clean_tkn_quotes(char *str);
int		count_spaces(char *str);
int		is_quote(char c);
int		is_redir(char c);
void	set_quote_state(int *is_in_quotes);
int		are_there_more_tokens(char *input);

// =============tree=============== //

void	pipe_error(void);
void	fork_error(void);
void	print_cmds(char **cmds);
char	*make_tree(t_shell *shell);
void	exec_tree(t_shell *shell, t_tree_node *node);
void	exec_cmd(t_shell *shell, t_tokens *node_content);
// Exec Tree Utils
int		is_heredoc_command(char **cmd);
int		handle_heredoc_exec(t_shell *shell, t_tree_node *node);
char	*find_path(char *cmd, t_env *envp);
void	check_if_builtin(char **cmd, char *envp);
int		has_redirection(t_tokens *tokens);
int		open_file(char *file_name, int flag);

// ============= redirections =============== //

void	handle_redirections(t_shell *shell, t_tokens *tokens);
int		is_infile(char *str);
int		is_outfile(char *str);
void	dup_from_input(int fd);
void	dup_to_output(int fd);
void	clean_redirs(t_tokens *tokens);

// ================== built-ins ==================== //
//=========== pwd command ===========//
int		do_pwd(char **command);


//=========== echo command ===========//

int		do_echo(char **command);

//=========== unset command ===========//

int		do_unset(t_env *env, char **command);
int		on_first_node(t_env **env);
void	clean_first_node(t_env *node);
void	clean_env_node_attributes(t_env *node);
int		remove_env_var(t_env *env, char *env_to_remove);

//=========== env command ============//

int		do_env(char **command, t_env *env);
void	print_env(t_env *env);
int		handle_env_error(char *command);

//=========== export command ==========//

int		do_export(t_env **env, char **command);
char	*only_name(char *str);
char	*only_value(char *str);
char	*only_operant(char *str);
void	print_sorted(t_env *env);
void	print_env_export(t_env *node);
int		check_var_name(char *var_name);
int		check_if_have_equal_sign(char *declaration);
int		search_in_env(t_env *env, char *searching_var);

//========= cd command ==========//

int		do_cd(t_shell *s_heredock, char **command);
int		cd_no_args(t_env *env);
int		cd_args(char **command);
int		check_file_type(char *dir_path);
int		handle_cd_error(char **command);
int		cd_opitionals(t_env *env, char **command);
void	refresh_pwd_oldpwd(t_shell *shell, char *old_pwd);

//========= exit command ==========//

void	do_exit(t_shell *shell, char **cmd);

// ===builtins utils=== //

int		get_height(char **array);
char	*ft_strjoin_free_s1(char *s1, char *s2);
int		ft_strcmp(char *str1, char *str2);
char	*join_str_char(char *s1, char s2);
int		check_exist_optionals(char **command);

// =============heredoc=============== //

t_heredock	*create_heredoc(t_tree_node *node);
t_heredock	*create_heredoc_node(t_tokens *key);
t_heredock	*free_heredock(t_heredock *heredock);
t_heredock	*create_heredoc_body(t_tree_node *node, int i);

int	creating_temp_file(char *write);
void	doing_key(t_heredock *heredock);
int	handle_heredoc(t_shell *shell, t_tokens *redir);
char		*ft_strjoin_w_new_line(char *s1, char *s2);
int			doing_heredock(t_shell *shell, t_heredock *heredock);

// =============handlers=============== //

void	cntrl_C();
void	cntrl_D();
void	cntrl_Backslash();
void	handle_commands(t_shell *shell);
void	signalHandler(int signum, siginfo_t *info, void *context);

// ============Expansion============== //

int		check_expand(char *str);
char	*takeoff_quotes(char *str);
char	*var_name(char *str, int start);
char	*handle_expension(t_env *env, char *str);
void	expand_token(t_env *env, t_tokens *token);
char	*re_wrinting_string(char *str, char *expand_value, int where_to_change, int var_len);

#endif

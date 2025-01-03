/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:12:10 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/03 16:25:24 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# define PIPE 1
# define INFILE 3
# define OUTFILE 4
# define HEREDOC 5
# define EXPANSION 6

# include <stdio.h>
# include <dirent.h>
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
	//t_heredock	*heredock;
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
	char			**cmd;
	struct s_cmds	*next;
}				t_cmds;

typedef struct s_tree_node
{
	void				*content;
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
	int					key_len;
	char				*key;
	char				*fullinput_until_key;
	struct s_heredock	*next;
}				t_heredock;

// =====================functions====================== //

t_tokens	*get_tokens(t_shell *shell, char *input);

int		is_separator(char c);
int		get_token_state(char *str);
int		get_token_type(char *str);
void	print_tokens(t_tokens *tokens);
void	giving_value_to_str(char *str, char *cmd, int strlen, int index_start);
int		handle_quotes(const char *str, int i, char quote_type);
int		word_count(char *str);
char	**build_cmd_array(t_tokens *tokens);
t_cmds	*build_cmd_list(char **cmds);
void	print_cmds(char **cmds);
int	is_builtin( t_shell *shell, char **command);
// TO ORGANIZE :p
void	print_individual_tkn(t_tokens *token);
int	check_open_brackets(const char *str);
int	check_open_quotes(const char *str);
char	*build_single_cmd(t_tokens **tokens, int index);
void	strjoin_and_replace(char **s1, char *s2);
int	count_words(char *str);
int	is_pipe_node(char **content);
int	clean_and_terminate(t_shell *shell);
int	clean_all_and_close(t_shell *shell);

// =============tokens=============== //

void	create_space_token(t_tokens *tokens);
char	*clean_tkn_quotes(char *str);
int		count_spaces(char *str);
int		is_quote(char c);

// =============tree=============== //

void	make_tree(t_shell *shell);
void	print_cmds(char **cmds);
void	exec_tree(t_shell *shell, t_tree_node *node);
void	free_tree(t_tree_node *head);
void	free_cmd_list(t_cmds *cmds);
void	pipe_error(void);
void	fork_error(void);

// Exec Tree Utils
char	*find_path(char *cmd, t_env *envp);
void    check_if_builtin(char **cmd, char *envp);


// =============built-ins=============== //

int		do_export(t_env **env, char **command);
int		do_env(char **command, t_env *env);
int		do_unset(t_env *env, char **command);
int		do_cd(t_shell *s_heredock, char **command);
int		do_pwd(char **command);
int		do_echo(char **command);

//==========envp shit===============//

void	print_env(t_env *env);
char	*only_value(char *str);
char	*only_name(char *str);
char	*only_operant(char *str);
int		check_var_name(char *var_name);

void	free_env_node(t_env *node);
int		search_in_env(t_env *env, char *searching_var);
int		check_if_have_equal_sign(char *declaration);
void	refresh_var_value(t_env *env, t_env *var_with_new_value, int behavior);
void	add_new_variable(t_env *env ,t_env *new_variable);
t_env	*creating_enviroment(char **envp);
t_env	*creating_env_var_w_no_value(char *full_declaration);
t_env	*creating_env_var(char *full_declaration);

// ===builtins utils=== //

void	print_sorted(t_env *env);
int		count_env(t_env *env);
void	zero_all_env(t_env *env);
int		on_first_node(t_env **env);
void	print_env_export(t_env *node);
int		check_file_type(char *dir_path);
int		handle_cd_error(char **command);
int		get_height(char **array);
char	*ft_strjoin_free_s1(char *s1, char *s2);
int		ft_strcmp(char *str1, char *str2);
char	*join_str_char(char *s1, char s2);
int		check_exist_optionals(char **command);
void	adding_var_in_list(t_env **env, t_env *node);
int		remove_env_var(t_env **env, char *env_to_remove);

// =============heredock=============== //

char		*ft_strjoin_w_new_line(char const *s1, char const *s2);
void		key_that_metters(t_heredock *last_node);
t_heredock	*doing_heredock(t_heredock *heredock);
t_heredock	*reading_until_last_key(t_heredock *heredock);

// =============handlers=============== //

void	cntrl_C();
void	cntrl_D();
void	cntrl_Backslash();
void	handle_commands(t_shell *shell);
void	signalHandler(int signum, siginfo_t *info, void *context);
char	*fill_str(char *str, int target_word, char separator);

// ============Expansion============== //

void	expand_token(t_env *env, t_tokens *token);
char	*takeoff_quotes(char *str);
int		check_expand(char *str);
char	*handle_expension(t_env *env, char *str);
char	*var_name(char *str, int start);
char	*re_wrinting_string(char *str, char *expand_value, int where_to_change, int var_len);
char	*get_env_var_value(t_env *env, char *var_searching);

#endif

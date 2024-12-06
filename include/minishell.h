/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:12:10 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/29 14:50:52 by dioferre         ###   ########.fr       */
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

# include <stdio.h>
# include <dirent.h>
# include <signal.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/libft.h"

typedef struct s_env
{
	char	*pwd;
	char	*old_pwd;
	char	*prefix;
	char	*path;
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

t_tokens	*get_tokens(char *input);

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
void	cmd(char **command);


// =============built-ins=============== //

void	do_cd(char **command);
void	do_pwd(char **command);
void	do_ls(char **command);
void	do_echo(char **command);

// =============heredock=============== //

char		*ft_strjoin_w_new_line(char const *s1, char const *s2);

void		key_that_metters(t_heredock *last_node);
t_heredock	*doing_heredock(t_heredock *heredock);
t_heredock	*reading_until_last_key(t_heredock *heredock);

// =============handlers=============== //

void	cntrl_C();
void	cntrl_D();
void	cntrl_Backslash();
void	handle_commands(t_tokens *tokens, t_env *env, char **envp);
void	signalHandler(int signum, siginfo_t *info, void *context);

char	*fill_str(char *str, int target_word, char separator);

// ============Expension============== //

void	*expand_token(t_tokens *token);
char	*takeoff_quotes(char *str);
int		check_expand(char *str);
char	*handle_expension(char *str);
char	*var_name(char *str, int start);
char	*re_wrinting_string(char *str, char *expand_value, int where_to_change, int var_len);

#endif

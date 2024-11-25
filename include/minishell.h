/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:12:10 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/25 17:00:44 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define true 1
# define false 0

# include <stdio.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft.h"

typedef struct s_env
{
	char	*pwd;
	char	*old_pwd;
	char	*prefix;
	char	*path;
}				t_env;


typedef struct s_tokens
{
	char			*token;
	int				type; // 0 str, 1 pipe, 2 & ,3 infile, 4 outfile, 5 heredoc, 6 expansion.
	int				state; //0 general, 1 single quote, 2 double quote, 3 expanded;
	int				index;
	struct	s_tokens	*next;

}				t_tokens;

// =====================functions====================== //

t_tokens	*get_tokens(char *input);

int		is_separator(char c);
int		get_token_state(char *str);
int		get_token_type(char *str);
void	print_tokens(t_tokens *tokens);
void	giving_value_to_str(char *str, char *cmd, int strlen, int index_start);
int		handle_quotes(const char *str, int i, char quote_type);
int		word_count(char *str);


// =============handlers=============== //
void	cntrl_C();
void	cntrl_D();
void	cntrl_Backslash();
void	handle_commands(t_tokens *tokens, t_env *env, char **envp);
void	signalHandler(int signum, siginfo_t *info, void *context);

char	*fill_str(char *str, int target_word, char separator);



#endif

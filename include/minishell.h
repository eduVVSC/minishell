/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:12:10 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/19 17:46:42 by dioferre         ###   ########.fr       */
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
	char	*path;
}				t_env;


typedef struct s_tokens
{
	char			*token;
	int				type; // 0 cmd, 1 pipe, 2 infile, 3 outfile.
	int				state; //0 general, 1 single quote, 2 double quote;
	int				index;
	struct s_token	*next;

}				t_tokens;

// =====================functions====================== //

t_tokens	*fill_node(void);
t_tokens	*get_tokens(char *input);

void	giving_value_to_str(char *str, char *cmd, int strlen, int index_start);
void	fill_tokens(t_tokens *tokens, int nr);
int	handle_quotes(const char *str, int i, char quote_type);
int	word_count(char *str);


// =============handlers=============== //
void	cntrl_C();
void	cntrl_D();
void	cntrl_Backslash();
void	signalHandler(int signum, siginfo_t *info, void *context);

char	*fill_str(char *str, int target_word, char separator);



#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:12:10 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/18 16:07:20 by dioferre         ###   ########.fr       */
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
	int			i;
	char		*cmd;
	char		**args;
	struct s_tokens	*next;

}				t_tokens;

// =====================functions====================== //

t_tokens	*fill_node(void);
t_tokens	*get_tokens(char *input);

void	giving_value_to_str(char *str, char *cmd, int strlen, int index_start);
void	fill_tokens(t_tokens *tokens, int nr);
int	handle_quotes(const char *str, int i, char quote_type);
int	word_count(char *str, char separator);


// =============handlers=============== //
void	cntrl_C();
void	cntrl_D();
void	cntrl_Backslash();
void	signalHandler(int signum, siginfo_t *info, void *context);

char	*fill_str(char *str, int target_word, char separator);



#endif

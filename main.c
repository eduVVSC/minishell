/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:14:53 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/03 17:26:37 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// observations:: Its already properly, setting the enviroment to run through, just need to fix the executions
// every function that can manage the env, should receve the address, no only the pointer, of the env list

void test_expand(t_env *env, t_tokens *tokens)
{
	printf("------------------------------\n");
	printf("\tafter the handle quotes\n");
	printf("------------------------------\n");
	while (tokens != NULL)
	{
		expand_token(env, tokens);
		printf("%s\n", tokens->token);
		tokens = tokens->next;
	}
}

t_env	*create_env_no_envp()
{
	t_env	*env;

	env = NULL;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->var_name = ft_strdup("PWD");
	env->operant = ft_strdup("=");
	env->var_value = getcwd(NULL, 0);

	env->next = creating_env_var_w_no_value("OLDPWD");
	env->next->next = creating_env_var("SHLVL=");
	env->next->next->next = NULL;
	return (env);
}

// take the envp from the start of the program and trasnform it into a linked list
t_env	*creating_enviroment(char **envp)
{
	t_env	*env_head;
	t_env	*tmp;
	int	i;

	i = 1;
	if (envp[0])
		env_head = creating_env_var(envp[0]);
	else
		return (create_env_no_envp());
	tmp = env_head;
	while (envp[i] != NULL)
	{
		tmp->next = creating_env_var(envp[i]);
		if (tmp->next != NULL)
			tmp = tmp->next;
		i++;
	}
	tmp = NULL;
	return (env_head);
}

t_shell	*setting_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = creating_enviroment(envp);
	shell->dir_now = ft_strjoin_free_s1(getcwd(NULL, 0), "$ ");
	shell->tokens = NULL;
	shell->tree = NULL;
	shell->cmd_list = NULL;
	return (shell);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free_env_node(tmp);
	}
}

void	free_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->token);
		free(tmp);
	}
}

int	clean_and_terminate(t_shell *shell)
{
	free_tree(shell->tree);
	free_tokens(shell->tokens);
	free_cmd_list(shell->cmd_list);
	free_env(shell->env);
	free(shell->dir_now);
	free(shell);
	exit(0);
}

int	clean_all_and_close(t_shell *shell)
{
	free_tree(shell->tree);
	free_tokens(shell->tokens);
	free_cmd_list(shell->cmd_list);
	free_env(shell->env);
	free(shell->dir_now);
	free(shell);
	return (0);
}

// when initializing without the envp, initialize pwd, oldpwd, shlvl
/* int	main(int ac, char **av, char **envp)
{
	t_shell		*shell;
	struct	sigaction	sa;
	char		*input;

	(void) ac;
	(void) av;
	shell = setting_shell(envp);
	if (!shell)
		exit (ft_printf("Program closing! Could not set shell\n"));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signalHandler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	while (1)
	{
		input = readline(shell->dir_now);
		if (!input)
		{
			free(input);
			exit(clean_all_and_close(shell));
		}
		shell->tokens = get_tokens(shell ,input);
		make_tree(shell);
//		print_tokens(shell->tokens); //action
//		handle_commands(shell);
		add_history(input);
		free(input);
	}
	return (0);
} */

int	main(int argc, char **argv, char **envp)
{
	t_shell		*shell;
	char **cmds;
	char *input = argv[1];
	int	i = 0;
	shell = setting_shell(envp);
	if (!shell)
		exit (ft_printf("Program closing! Could not set shell\n"));
	shell->tokens = get_tokens(shell ,input);
	make_tree(shell);
}

/* ---test heardock*/
/* int	main(int ac, char **av,char **envp)
{
	t_heredock *heredock;
	t_heredock *node1;
	t_heredock *node2;

	heredock = malloc(sizeof(t_heredock));
	node1 = malloc(sizeof(t_heredock));
	node2 = malloc(sizeof(t_heredock));

	heredock->key = "1";
	node1->next = node1;
	node1->key = "2";
	node1->next = NULL;
	node2->key = "2";
	node2->next = NULL;

	heredock = doing_heredock(heredock);
	printf("%s\n", heredock->fullinput_until_key);
	return (0);
}
 */

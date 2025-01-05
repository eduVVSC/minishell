
#include "minishell.h"

/// @brief Create the enviroment when envp is null
/// @return (Head node - success) (NULL - malloc error)
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

/// @brief create the enviroment with the envp inputs
/// @param envp
/// @return (Head node - success) (NULL - malloc error)
t_env	*create_env_envp(char **envp)
{
	t_env	*env_head;
	t_env	*tmp;
	int	i;

	i = 1;
	env_head = creating_env_var(envp[0]);
	if (!env_head)
		return (NULL);
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

/// @brief create the enviroment with the envp inputs
/// @param envp
/// @return (Head node - success) (NULL - malloc error)
void	*create_env(t_shell *shell, char **envp)
{
	if (envp[0])
		shell->env = create_env_envp(envp);
	else
		shell->env = create_env_no_envp();
	if (!shell->env)
		clean_and_terminate(shell);
}

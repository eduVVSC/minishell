
#include "minishell.h"

int	env_height(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	**transfrom_env_to_array(t_env *env)
{
	char	**envp;
	int		height;
	int		i;

	i = 0;
	height = env_height(env);
	envp = malloc(sizeof(char **) * (height + 1));
	if (!envp)
		return (NULL);
	while (env)
	{
		envp[i] = ft_strdup(env->var_name);
		if (env->operant)
		{
			envp[i] = ft_strjoin_free_s1(envp[i], env->operant);
			if (env->var_name)
				envp[i] = ft_strjoin_free_s1(envp[i], env->var_value);
		}
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}


#include "include/minishell.h"

void	print_env_export(t_env *node)
{
	printf("declare -x ");
	printf("%s", node->var_name);
	if (node->operant != NULL)
	{
		printf("%s", node->operant);
		printf("\"%s\"", node->var_value);
	}
	printf("\n");
}


void	print_sorted(t_env *env)
{
	t_env	*tmp;
	t_env	*lowest_node;
	int		many_prints;
	int		i;

	i = -1;
	many_prints = count_env(env);
	while (++i < many_prints)
	{
		tmp = env;
		lowest_node = tmp;
		while (tmp)
		{
			if (tmp->printed == 0)
			{
				if (lowest_node->printed == 1 && tmp->printed == 0)
					lowest_node = tmp;
				if (ft_strcmp(lowest_node->var_name, tmp->var_name) > 0)
					lowest_node = tmp;
			}
			tmp = tmp->next;
		}
		lowest_node->printed = 1;
		print_env_export(lowest_node);
	}
}

t_env	*create_env_no_envp()
{
	t_env	*env;

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

void remove_1st_var(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	(*env) = (*env)->next;
	free_env_node(tmp);
}

int	main(int ac, char **av)
{
	t_env	*env;

	env = create_env_no_envp();
	print_env_export(env);
	remove_1st_var(&env);
	print_env_export(env);
}

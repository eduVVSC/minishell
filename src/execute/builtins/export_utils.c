
#include "minishell.h"

/// @brief Create a complete enviroment variable(name+operant+value)
/// @param full_declaration
/// @return (t_env var -> succes)(NULL -> malloc error)
t_env	*creating_env_var(char *full_declaration)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->var_name = only_name(full_declaration); // name
	//printf("working name\n");
	new_node->operant = only_operant(full_declaration); // operant
	//printf("working operant\n");
	new_node->var_value = only_value(full_declaration); // value
	new_node->next = NULL;
	//printf("working value\n");
	new_node->printed = 0;

	if (check_var_name(new_node->var_name) == 1) // needs to free the node
	{
		free_env_node(new_node);
		return (NULL);
	}
	//printf("breaking here 1\n");
	if (new_node->operant[0] == '=')
		new_node->behaviour = 0;
	else
		new_node->behaviour = 1;
	//printf("breaking here 2\n");
	return (new_node);
}

/// @brief Create a  enviroment variable without value nor operant(name)
/// @param full_declaration
/// @return (t_env var -> succes) (NULL -> malloc error)
t_env	*creating_env_var_w_no_value(char *full_declaration)
{
	t_env	*new_node;

	if (check_var_name(full_declaration) == 1)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->var_name = ft_strdup(full_declaration); // name
	new_node->operant = 0; // operant
	new_node->var_value = NULL; // value
	return (new_node);
}


/// @brief Print one node in the export format "declare -x [var]"
/// @param node
void	print_env_export(t_env *node)
{
	ft_printf("declare -x ");
	ft_printf("%s", node->var_name);
	if (node->operant != NULL)
	{
		ft_printf("%s", node->operant);
		ft_printf("\"%s\"", node->var_value);
	}
	ft_printf("\n");
}

/// @brief Count how many nodes are in the env list
/// @param env
/// @return many_nodes
int	count_env(t_env *env)
{
	int	i;

	i = 0;
	if (!env || env->var_name == NULL)
		return (0);
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

/// @brief Zero all the printed values of the env nodes
void	zero_all_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		tmp->printed = 0;
		tmp = tmp->next;
	}
}

/// @brief Will add the new_variable in the list whenever they found one string that is "lower" than this one
/// @param env
/// @param new_variable
void	add_new_variable(t_env *env ,t_env *new_variable)
{
	t_env	*tmp;
	t_env	*replaced_node;

	tmp = env;
	if (new_variable->behaviour == 1)
	{
		new_variable->behaviour = 0;
		free(new_variable->operant);
		new_variable->operant = ft_strdup("=");
	}
	while (ft_strcmp(tmp->var_name, new_variable->var_name) < 0 && tmp->next != NULL)
		tmp = tmp->next;
	replaced_node = tmp->next;
	tmp->next = new_variable;
	new_variable->next = replaced_node;
}

/// @brief Will search for the variable in env and refresh it's value.
/// @param env
/// @param var_with_new_value
/// @param behaviour (define if its will add(1) or replace (0))
void	refresh_var_value(t_env *env, t_env *var_with_new_value, int behavior)
{
	if (var_with_new_value->var_value == NULL)
		return (free_env_node(var_with_new_value));
	while (ft_strcmp(env->var_name, var_with_new_value->var_name) != 0 && env != NULL)
		env = env->next;
	if (env == NULL)
		return ;
	if ((!env->operant || env->operant == 0) && var_with_new_value->operant != 0)
		env->operant = ft_strdup("=");
	if (behavior == 0 || !env->var_value)
	{
		free(env->var_value);
		env->var_value = ft_strdup(var_with_new_value->var_value);
	}
	else if (behavior == 1)
		env->var_value = ft_strjoin(env->var_value, var_with_new_value->var_value);
	free_env_node(var_with_new_value); //free
}

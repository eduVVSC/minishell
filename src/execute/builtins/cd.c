/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edvieira <edvieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:52:58 by edvieira          #+#    #+#             */
/*   Updated: 2025/01/03 18:14:36 by edvieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/// @brief Handle the "cd -..." the only executable one is the "cd -" that will try to go to the OLDPWD.
/// @brief If it won't work, it delivers a error message to the stderror
/// @return (0 -> success) (2 -> error [OLDPWD not set or difrrent optional])
int	cd_opitionals(t_env *env, char **command)
{
	char	*where_to;

	if (ft_strcmp(command[1], "-") == 0)
	{
		where_to = get_env_var_value(env, "OLDPWD");
		if (!where_to)
		{
			ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
			return (2);
		}
		chdir(where_to);
		return (0);
	}
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(command[1], 2);
	ft_putstr_fd(" not set\n", 2);
	return (2);
}

/// @brief Handle the "cd", in this case it should go to the HOME, if not set, it will deliver the error message
/// @return (0 -> success) (2 -> error [HOME not set])
int	cd_no_args(t_env *env)
{
	int	returned_from_exec;
	char	*home;

	home = get_env_var_value(env, "HOME");
	if(home == NULL)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return (1);
	}
	returned_from_exec = chdir(home);
	if (returned_from_exec == -1)
		return (2);
	return (0);
}

/// @brief Handle the "cd [.]", it will try to go to the expecified path, if bad path will deliver the error message to the stderror
/// @return (0 -> success) (2 -> error [not a good path])
int	cd_args(char **command)
{
	int	returned_value;

	returned_value = chdir(command[1]);
	if (returned_value == -1)
		return (handle_cd_error(command));
	return (0);
}

/// @brief Will refresh or create the OLDPWD and PWD env variables to the current and latest dir
void	refresh_pwd_oldpwd(t_shell *shell, char *old_pwd)
{
	t_env	*temp;
	t_env	*temp2;

	temp = malloc(sizeof(t_env));
	if (!temp)
		return ;
	temp->behaviour = 0;
	temp->var_name = ft_strdup("PWD");
	temp->operant = ft_strdup("=");
	temp->var_value = getcwd(NULL, 0);
	free (shell->dir_now);
	shell->dir_now = ft_strjoin(temp->var_value, "$ ");
	adding_var_in_list(&shell->env, temp);
	temp2 = malloc(sizeof(t_env));
	if (!temp2)
		return ;
	temp2->behaviour = 0;
	temp2->var_name = ft_strdup("OLDPWD");
	temp2->operant = ft_strdup("=");
	temp2->var_value = old_pwd;
	adding_var_in_list(&shell->env, temp2);
}

/// @brief Do the cd command
/// @return (0 -> success) (2 -> error)
int	do_cd(t_shell *shell, char **command)
{
	int		many_args;
	int		returned_from_exec;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (get_height(command) > 2)
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
	many_args = check_exist_optionals(command);
	if (many_args == -1)
		returned_from_exec = cd_opitionals(shell->env, command);
	else if (many_args == 1)
		returned_from_exec = cd_no_args(shell->env);
	else
		returned_from_exec = cd_args(command);
	if (returned_from_exec == 0)
		refresh_pwd_oldpwd(shell, old_pwd);
	return (returned_from_exec);
}

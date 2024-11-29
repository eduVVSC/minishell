#include "minishell.h"


void	setting_to_print(char **command)
{
	int	i;

	i = 1;
	while(command[i])
	{
		if (check_expand(command[i]) != -1)
			command[i] = handle_expension(command[i]);
		i++;
	}
}

void	do_echo(char **command)
{
	command[0] = ft_strjoin("/bin/", command[0]);
	setting_to_print(command);


	execve(command[0], command, NULL);
}

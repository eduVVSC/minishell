#include "minishell.h"

void	do_pwd(char **command)
{
	command[0] = ft_strjoin("/bin/", command[0]);

	execve(command[0], command, NULL);
}


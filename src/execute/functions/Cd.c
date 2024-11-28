#include "minishell.h"

void	do_cd(char **command)
{
	command[0] = ft_strjoin("/bin/", command[0]);

	execve(command[0], command, NULL);
}

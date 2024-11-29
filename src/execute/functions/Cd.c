#include "minishell.h"

void	do_cd(char **command)
{
	char	*filename;

	getenv("pwd");
	filename = ft_strjoin(getenv("pwd") ,command[1]);
	chdir(filename);
	//execve(command[0], command, NULL);
}

#include "minishell.h"

static int	get_exit_code(char **cmd)
{
	int	exit_code;

	if (cmd[1])
		exit_code = ft_atoi(cmd[1]);
	else
		exit_code = 0;
	if (exit_code < 0 || exit_code > 255)
		exit_code = 255;
	return (exit_code);
}


void	do_exit(t_shell *shell, char **cmd)
{
	int	exit_code;

	exit_code = get_exit_code(cmd);
	printf("exiting...\n");
	ft_free_double_arr(&cmd);
	clean_and_terminate_with_status(shell, exit_code);
}
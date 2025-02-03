
#include "minishell.h"

/// @brief Will check the use of '!' in a input
/// @param input
/// @param pos
/// @param val_num
/// @return (true(1) -> good use of exclamation) (false(0) -> bad use of exclamation)
int	exclamation_validation(char *input, int pos, int val_num)
{
	if ((input[pos] == '!' && input[pos + 1] == '\'' && val_num == single_quo))
		return (true);
	else if ((input[pos] == '!' && input[pos + 1] == '\"' && val_num == double_quo))
		return (true);
	else if (input[pos] == '!' && (input[pos + 1] != ' ' && input[pos + 1] != '\0'))
	{
		ft_putstr_fd("bash: event not found\n", 2);
		return (false);
	}
	return (true);
}

int	parenthesis_validation(char *input, int pos)
{
	char	*str;

	ft_putstr_fd("bash: syntax error near unexpected token '" , 2);
	ft_putchar_fd(input[pos], 2);
	ft_putstr_fd("'\n", 2);
	return (2);
}

int	single_quo_validation(int val_num)
{
	if (val_num == general)
		return (single_quo);
	else if(val_num == single_quo)
		return (general);
	return (val_num);
}

int	double_quo_validation(int val_num)
{
	if (val_num == general)
		return (double_quo);
	else if(val_num == double_quo)
		return (general);
	return (val_num);
}

int	check_input(t_shell *shell, char *input)
{
	int	i;
	int	val_num;

	i = -1;
	val_num = general;
	if (!input)
		exit (clean_all_and_close(shell));
	if (input[0] == '\0' || input[0] == '\n')
		return (-1);
	while (input[++i])
	{
		if (input[i] == '\'')
			val_num = single_quo_validation(val_num);
		else if (input[i] == '\"')
			val_num = double_quo_validation(val_num);
		else if ((input[i] == '(' || input[i] == ')') && val_num == general)
			return (parenthesis_validation(input, i));
		else if (exclamation_validation(input, i, val_num) == false)
			return (1);
	}
	return (val_num);
}

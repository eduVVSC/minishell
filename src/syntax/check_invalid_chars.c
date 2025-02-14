
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
		ft_putstr_fd("minishell: event not found\n", 2);
		return (false);
	}
	return (true);
}

int	parenthesis_validation(char *input, int pos)
{
	char	*str;

	ft_putstr_fd("minishell: syntax error near unexpected token '" , 2);
	ft_putchar_fd(input[pos], 2);
	ft_putstr_fd("'\n", 2);
	return (2);
}

int	check_invalid_chars(char *input, int i)
{
	int	val_num;

	val_num = general;
	while (input[i])
	{
		if ((input[i] == '(' || input[i] == ')') && val_num == general)
			return (parenthesis_validation(input, i));
		else if (exclamation_validation(input, i, val_num) == false)
			return (1);
		else if ((input[i] == '\\' || input[i] == ';') && val_num == GENERAL)
			return (print_syntax_error(INVALID_CHAR_ERROR), 1);
		i++;
	}
	return (val_num);
}

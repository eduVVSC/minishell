#include "minishell.h"



/*char *only_name(char *str)
{
	char	*name;
	int	i;

	i  = 0;
	name = malloc(sizeof(char) * 1);
	name = NULL;
	while(str[i] != "=")
	{
		name = ft_strjoin(name, str[i]);
		i++;
	}
	return (name);
}

 char *only_value(char *str)
{
	char	*value;
	int	i;

	i  = 0;
	value = malloc(sizeof(char) * 1);
	value = NULL;
	while(str[i] != "=")
		i++;
	while(str[i] != "=")
	{
		value = ft_strjoin(value, str[i]);
		i++;
	}
	return (value);

}

char **separating_name_value(char *full_declaration)
{
	char	**separated;
	int		i;

	i  = 0;
	separated = malloc(sizeof(char *) * 3);
	separated[0] = only_name(full_declaration); // name
	separated[1] = ; // value
	separated[2] = 0; // 0
}*/

void do_export(t_tokens *token)
{

}

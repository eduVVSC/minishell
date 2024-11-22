/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:39:37 by dioferre          #+#    #+#             */
/*   Updated: 2024/11/22 17:06:36 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	t_tokens *tokens;
	char *input = argv[1];
	int	i = 0;
	tokens = get_tokens(input);
	print_tokens(tokens);
}

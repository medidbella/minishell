/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:00:46 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/24 15:09:00 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_2(int which)
{
	if (which == 9)
		ft_putstr_fd
		("minishell: syntax error near unexpected token `newline'\n", 2);
	else if (which == 10)
		ft_putstr_fd
		("minishell: syntax error the '||' operator is not supported.\n", 2);
	else if (which == 11)
	{
		ft_putstr_fd("minishell: syntax error pipe '|' ", 2);
		ft_putstr_fd("cannot be at the start or end of a command.\n", 2);
	}
}

int	print_errors(int which)
{
	if (which == 1)
		ft_putstr_fd("minishell: unmatched quotation mark detected.\n", 2);
	else if (which == 2)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (which == 3)
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
	else if (which == 4)
		ft_putstr_fd("minishell: syntax error near unexpected token `<<<'\n",
			2);
	else if (which == 5)
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
	else if (which == 6)
		ft_putstr_fd("minishell: syntax error near unexpected token `<>'\n", 2);
	else if (which == 7)
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
	else if (which == 8)
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	else
	{
		print_2(which);
	}
	g_status->r_val = 2;
	return (0);
}

int	do_expand(char *limiter)
{
	int	i;

	i = 0;
	while (limiter[i])
	{
		if (limiter[i] == REMOVE)
			return (0);
		i++;
	}
	return (1);
}

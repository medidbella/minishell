/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 03:26:38 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/21 09:47:57 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_errors(void)
{
	ft_putstr_fd("syntax error\n", 2);
	g_status->r_val = 2;
	return (0);
}

int	pipe_errors_2(char *read_line, int i, int x)
{
	int	checker;

	checker = 0;
	while (read_line[++x] && read_line[x] != '|')
	{
		if (read_line[x] != ' ')
		{
			checker = 1;
			break ;
		}
	}
	if (!checker)
		return (print_errors());
	checker = 0;
	x = i;
	while (read_line[++x])
	{
		if (read_line[x] != '|' && read_line[x] != ' ')
			checker = 1;
	}
	if (!checker)
		return (print_errors());
	return (1);
}

static int	out_put_and_append_red(char *read_line, int *i)
{
	int	checker;

	(*i)++;
	checker = 0;
	if (read_line[*i] == ' ' || read_line[*i] == '>')
		(*i)++;
	while (read_line[*i] && read_line[*i] != '|')
	{
		if (read_line[*i] != ' ' && read_line[*i] != '>'
			&& read_line[*i] != '<')
		{
			checker = 1;
			break ;
		}
		if (read_line[*i] == '>' || read_line[*i] == '<')
			return (print_errors());
		(*i)++;
	}
	if (!checker)
		return (print_errors());
	return (1);
}

int	input_red_and_her_doc(char *read_line, int *i)
{
	int	checker;

	checker = 0;
	(*i)++;
	if (read_line[*i] == ' ' || read_line[*i] == '<')
		(*i)++;
	while (read_line[*i] && read_line[*i] != '|')
	{
		if (read_line[*i] != ' ' && read_line[*i] != '>'
			&& read_line[*i] != '<')
		{
			checker = 1;
			break ;
		}
		if (read_line[*i] == '>' || read_line[*i] == '<')
			return (print_errors());
		(*i)++;
	}
	if (!checker)
		return (print_errors());
	return (1);
}

int	redirection_errors(char *read_line)
{
	int	i;

	i = 0;
	while (read_line[i])
	{
		if (read_line[i] == '>')
		{
			if (!out_put_and_append_red(read_line, &i))
				return (0);
		}
		else if (read_line[i] == '<')
		{
			if (!input_red_and_her_doc(read_line, &i))
				return (0);
		}
		else
			i++;
	}
	return (1);
}

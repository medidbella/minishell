/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 03:26:38 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/24 14:56:04 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	continue_checking(char *read_line, int *i)
{
	if (read_line[*i] == '>' && read_line[*i + 1] == '>')
		return (print_errors(3));
	else if (read_line[*i] == '<' && read_line[*i + 1] == '<'
		&& read_line[*i + 1] && read_line[*i + 2] == '<')
		return (print_errors(4));
	else if (read_line[*i] == '<' && read_line[*i + 1] == '<')
		return (print_errors(5));
	else if (read_line[*i] == '<' && read_line[*i + 1] == '>')
		return (print_errors(6));
	else if (read_line[*i] == '>')
		return (print_errors(7));
	else if (read_line[*i] == '<')
		return (print_errors(8));
	return (1);
}

int	pipe_errors_2(char *read_line, int i, int x, int checker)
{
	while (read_line[++x] && read_line[x] != '|')
	{
		if (read_line[x] != ' ')
		{
			checker = 1;
			break ;
		}
	}
	if (!read_line[x])
		return (print_errors(11));
	if (!checker && read_line[i + 1] == '|')
		return (print_errors(10));
	if (!checker)
		return (print_errors(2));
	checker = 0;
	x = i;
	while (read_line[++x])
	{
		if (read_line[x] != '|' && read_line[x] != ' ')
			checker = 1;
	}
	if (!checker)
		return (print_errors(2));
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
		if (!continue_checking(read_line, i))
			return (0);
		(*i)++;
	}
	if (read_line[*i] == '|' && read_line[(*i) + 1] == '|')
		return (print_errors(10));
	if (read_line[*i] == '|')
		return (print_errors(2));
	if (!checker)
		return (print_errors(9));
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
		if (!continue_checking(read_line, i))
			return (0);
		(*i)++;
	}
	if (!checker)
		return (print_errors(9));
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

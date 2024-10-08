/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:19:10 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/24 14:56:16 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	skip_pipes_inside_quotes(char *read_line, int *i)
{
	if (read_line[*i] == 39)
	{
		(*i)++;
		while (read_line[*i] != 39)
			(*i)++;
	}
	else if (read_line[*i] == '"')
	{
		(*i)++;
		while (read_line[*i] != '"')
			(*i)++;
	}
}

static int	pipe_errors(char *read_line)
{
	int	i;
	int	checker;

	i = 0;
	checker = 0;
	while (read_line[i] == ' ')
		i++;
	if (read_line[i] == '|')
		return (print_errors(11));
	while (read_line[i])
	{
		if (read_line[i] != ' ' && read_line[i] != '|')
			checker = 1;
		skip_pipes_inside_quotes(read_line, &i);
		if (read_line[i] == '|')
		{
			if (checker == 0)
				return (print_errors(2));
			if (!pipe_errors_2(read_line, i, i, 0))
				return (0);
		}
		i++;
	}
	return (1);
}

static int	single_quotes_errors(char *read_line, int *i, int checker)
{
	if (!checker)
		return (print_errors(1));
	if (read_line[*i] == 39)
	{
		checker = 0;
		(*i)++;
		while (read_line[*i])
		{
			if (read_line[*i] == 39)
			{
				checker = 1;
				break ;
			}
			else if (read_line[*i] == '<')
				read_line[*i] = IN_RED;
			else if (read_line[*i] == '>')
				read_line[*i] = OUT_RED;
			(*i)++;
		}
		if (!checker)
			return (print_errors(1));
	}
	return (1);
}

static int	quotes_errors(char *read_line, int checker)
{
	int	i;

	i = -1;
	while (read_line[++i])
	{
		if (read_line[i] == '"')
		{
			checker = 0;
			while (read_line[++i])
			{
				if (read_line[i] == '"')
				{
					checker = 1;
					break ;
				}
				else if (read_line[i] == '<')
					read_line[i] = IN_RED;
				else if (read_line[i] == '>')
					read_line[i] = OUT_RED;
			}
		}
		if (!single_quotes_errors(read_line, &i, checker))
			return (0);
	}
	return (1);
}

int	ft_errors(char *read_line)
{
	int	i;

	i = 0;
	if (read_line[i] == 0)
		return (0);
	if (!quotes_errors(read_line, 1))
		return (0);
	white_spaces(read_line);
	if (!pipe_errors(read_line))
		return (0);
	if (!redirection_errors(read_line))
		return (0);
	return (1);
}

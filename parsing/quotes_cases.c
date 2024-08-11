/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:37:16 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/08 15:09:12 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	case_of_pipe_inside_quotes_1(char *read_line)
{
	int	i;

	i = -1;
	while (read_line[++i])
	{
		if (read_line[i] == '"')
		{
			while (read_line[++i] != '"')
			{
				if (read_line[i] == '|')
					read_line[i] = -1;
			}
		}
		else if (read_line[i] == 39)
		{
			while (read_line[++i] != 39)
			{
				if (read_line[i] == '|')
					read_line[i] = -1;
			}
		}
	}
}

void	case_of_pipe_inside_quotes_2(char **splited)
{
	int	i;
	int	x;

	i = -1;
	while (splited[++i])
	{
		x = -1;
		while (splited[i][++x])
		{
			if (splited[i][x] == -1)
				splited[i][x] = '|';
		}
	}
}

static void	case_of_single_quotes(char *splited, int *x)
{
	splited[(*x)++] = REMOVE;
	while (splited[*x] != 39)
	{
		if (splited[*x] == ' ')
			splited[*x] = SPACES;
		else if (splited[*x] == '"')
			splited[*x] = D_QUOTES;
		else if (splited[*x] == '$')
			splited[*x] = DOLLAR;
		else if (splited[*x] == '<')
			splited[*x] = IN_RED;
		else if (splited[*x] == '>')
			splited[*x] = OUT_RED;
		(*x)++;
	}
	splited[*x] = REMOVE;
}

static void	case_of_double_quotes(char *splited, int *x)
{
	splited[(*x)++] = REMOVE;
	while (splited[*x] != '"')
	{
		if (splited[*x] == 39)
			splited[*x] = S_QUOTES;
		else if (splited[*x] == ' ')
			splited[*x] = SPACES;
		else if (splited[*x] == '<')
			splited[*x] = IN_RED;
		else if (splited[*x] == '>')
			splited[*x] = OUT_RED;
		else if ((splited[*x] == '$') && ((!splited[(*x) + 1])
				|| (splited[(*x) + 1] == ' ') || (splited[(*x) + 1] == 39)
				|| (splited[(*x) + 1] == '"') || (splited[(*x) + 1] == '$')))
			splited[*x] = DOLLAR;
		(*x)++;
	}
	splited[*x] = REMOVE;
}

int	quotes_cases_1(char **splited)
{
	int		i;
	int		x;

	i = -1;
	while (splited[++i])
	{
		x = 0;
		while (splited[i][x])
		{
			if (splited[i][x] == 39)
				case_of_single_quotes(splited[i], &x);
			else if (splited[i][x] == '"')
				case_of_double_quotes(splited[i], &x);
			x++;
		}
		case_of_dollar_sign(splited[i]);
		case_of_exit_statu(splited[i]);
	}
	return (1);
}

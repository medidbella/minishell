/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_cases_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:43:31 by alaktari          #+#    #+#             */
/*   Updated: 2024/07/22 10:42:07 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_there_single_quotes(char *splited)
{
	int	i;

	i = -1;
	while (splited[++i])
	{
		if (splited[i] == '"')
		{
			i++;
			while (splited[i] != '"')
				i++;
		}
		if (splited[i] == 39)
			return (1);
	}
	return (0);
}

void	check_cases(char *splited, int *x, int *y, char *new_str)
{
	while (splited[(*x)])
	{
		if (splited[(*x)] == '$' && splited[(*x) + 1] == 39)
			(*x)++;
		else if (splited[(*x)] == 39 && (*x) && splited[(*x) - 1] == '$')
		{
			(*x)++;
			while (splited[(*x)] != 39 && splited[(*x)])
				new_str[(*y)++] = splited[(*x)++];
		}
		else if (splited[(*x)] != 39 && splited[(*x)] != '$' && splited[(*x)])
			new_str[(*y)++] = splited[(*x)++];
		else if (splited[(*x)] == '$' && (*x) && splited[(*x) - 1] == 39)
		{
			new_str[(*y)++] = -2;
			(*x)++;
		}
		else if (splited[(*x)] == '$')
			new_str[(*y)++] = splited[(*x)++];
		else
			(*x)++;
	}
}

int	remove_single_quotes(char **splited, int i, int x, int y)
{
	char	*new_str;

	while (splited[++i])
	{
		if (!is_there_single_quotes(splited[i]))
			continue ;
		new_str = malloc(sizeof(char) * (ft_strlen(splited[i]) + 1));
		if (!new_str)
			return (0);
		x = 0;
		y = 0;
		while (splited[i][x])
			check_cases(splited[i], &x, &y, new_str);
		new_str[y] = '\0';
		free(splited[i]);
		splited[i] = new_str;
	}
	return (1);
}

void	dollar_sign_in_list(t_options *list)
{
	char	*in_out;
	int		x;

	while (list)
	{
		in_out = NULL;
		if (list->limiter)
			in_out = list->limiter;
		else if (list->input)
			in_out = list->input;
		else if (list->out)
			in_out = list->out;
		if (in_out)
		{
			x = 0;
			while (in_out[x])
			{
				if (in_out[x] == -2)
					in_out[x] = '$';
				x++;
			}
		}
		list = list->next;
	}
}

void	return_dollar_sign(t_input *input)
{
	int			i;
	int			x;
	t_options	*list;

	while (input)
	{
		if (input->cmd_av)
		{
			i = 0;
			while (input->cmd_av[i])
			{
				x = 0;
				while (input->cmd_av[i][x])
				{
					if (input->cmd_av[i][x] == -2)
						input->cmd_av[i][x] = '$';
					x++;
				}
				i++;
			}
		}
		list = input->list;
		dollar_sign_in_list(input->list);
		input = input->next;
	}
}

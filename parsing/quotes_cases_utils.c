/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_cases_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 22:47:56 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/14 12:54:47 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	replace_special_chars(char *p_to_char)
{
	if (*p_to_char == S_QUOTES)
		*p_to_char = 39;
	else if (*p_to_char == D_QUOTES)
		*p_to_char = '"';
	else if (*p_to_char == DOLLAR)
		*p_to_char = '$';
	else if (*p_to_char == SPACES)
		*p_to_char = ' ';
	else if (*p_to_char == IN_RED)
		*p_to_char = '<';
	else if (*p_to_char == OUT_RED)
		*p_to_char = '>';
}

static int	for_list(t_options *list, int x)
{
	char	**str;
	char	*new_str;

	while (list)
	{
		if (list->input)
			str = &(list->input);
		else if (list->out)
			str = &(list->out);
		else if (list->limiter)
			str = &(list->limiter);
		else
			return (1);
		x = -1;
		while ((*str)[++x])
			replace_special_chars(&((*str)[x]));
		new_str = get_return_value(*str);
		if (!new_str)
			return (0);
		*str = new_str;
		list = list->next;
	}
	return (1);
}

int	quotes_cases_2(t_input *input)
{
	int		i;
	int		x;
	char	*new_cmd;

	while (input)
	{
		if (input->cmd_av)
		{
			i = -1;
			while (input->cmd_av[++i])
			{
				x = -1;
				while (input->cmd_av[i][++x])
					replace_special_chars(&(input->cmd_av[i][x]));
				new_cmd = get_return_value(input->cmd_av[i]);
				if (!new_cmd)
					return (0);
				input->cmd_av[i] = new_cmd;
			}
		}
		if (!for_list(input->list, 0))
			return (0);
		input = input->next;
	}
	return (1);
}

void	case_of_dollar_sign(char *splited)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		if ((splited[i] == '$') && (splited[i + 1] == REMOVE))
			splited[i] = REMOVE;
		else if (splited[i] == '$' && splited[i + 1] == '$')
			splited[i] = DOLLAR;
		i++;
	}
}

void	case_of_exit_statu(char *splited)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		if (splited[i] == '$' && splited[i + 1] == '?')
		{
			splited[i] = EXIT_STATUS;
			i++;
			splited[i] = EXIT_STATUS;
		}
		else if (splited[i] == '$' && splited[i + 1] == '$')
		{
			while (splited[i] == '$')
				splited[i++] = DOLLAR;
			i--;
		}
		i++;
	}
}

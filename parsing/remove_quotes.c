/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 02:42:03 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/17 15:37:40 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	there_are_quotes(char *splited)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		if (splited[i] == REMOVE)
			return (1);
		i++;
	}
	return (0);
}

static int	get_new_len(char *splited)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (splited[i])
	{
		if (splited[i] != REMOVE && splited[i] != REMOVE)
			len++;
		i++;
	}
	return (len);
}

char	*start_removing(char *splited)
{
	char	*new_splited;
	int		len;
	int		i;
	int		x;

	i = -1;
	len = 0;
	new_splited = splited;
	if (there_are_quotes(splited))
	{
		len = get_new_len(splited) + 1;
		new_splited = malloc(sizeof(char) * len);
		if (!new_splited)
			return (NULL);
		x = 0;
		i = -1;
		while (splited[++i])
		{
			if (splited[i] != REMOVE)
				new_splited[x++] = splited[i];
		}
		new_splited[x] = 0;
		free(splited);
	}
	return (new_splited);
}

static int	remove_quotes_for_list(t_options *list)
{
	char	**p_to;
	char	*new_str;

	while (list)
	{
		if (list->input)
			p_to = &(list->input);
		else if (list->out)
			p_to = &(list->out);
		else if (list->limiter)
			p_to = &(list->limiter);
		else
			return (1);
		new_str = start_removing(*p_to);
		if (!new_str)
			return (0);
		*p_to = new_str;
		list = list-> next;
	}
	return (1);
}

int	remove_quotes(t_input *input, t_input *head)
{
	int		i;
	char	*new_str;

	while (input)
	{
		if (input->cmd_av)
		{
			i = 0;
			while (input->cmd_av[i])
			{
				new_str = start_removing(input->cmd_av[i]);
				if (!new_str)
					return (0);
				input->cmd_av[i] = new_str;
				i++;
			}
		}
		if (!remove_quotes_for_list(input->list))
			return (0);
		input = input->next;
	}
	return (check_built_in(head));
}

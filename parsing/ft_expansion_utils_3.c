/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_utils_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 02:35:10 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/22 17:44:02 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	only_special_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != NOT_EXIST)
			return (0);
		i++;
	}
	return (1);
}

int	special_and_normale_chars(char *s)
{
	int	i;
	int	checker_1;
	int	checker_2;

	i = 0;
	checker_1 = 0;
	checker_2 = 0;
	while (s[i])
	{
		if (s[i] != NOT_EXIST && !checker_1)
			checker_1 = 1;
		else if (s[i] == NOT_EXIST && !checker_2)
			checker_2 = 1;
		if (checker_1 && checker_2)
			return (1);
		i++;
	}
	return (0);
}

int	remove_special_chars(char **str)
{
	char	*temp;
	char	*new_str;
	int		i;
	int		x;

	i = 0;
	x = 0;
	temp = malloc(sizeof(char) * (ft_strlen(*str) + 1));
	if (!temp)
		return (0);
	while ((*str)[i])
	{
		if ((*str)[i] != NOT_EXIST)
			temp[x++] = (*str)[i];
		i++;
	}
	temp[x] = 0;
	new_str = ft_strdup(temp);
	if (!new_str)
		return (free(temp), 0);
	free(*str);
	free(temp);
	(*str) = new_str;
	return (1);
}

static int	check_for_list(t_options *list)
{
	char	**ptr;

	while (list)
	{
		if (list->input)
			ptr = &(list->input);
		else if (list->out)
			ptr = &(list->out);
		if (!(list->limiter) && only_special_chars(*ptr))
		{
			free(*ptr);
			*ptr = NULL;
		}
		else if (!(list->limiter) && special_and_normale_chars(*ptr))
		{
			if (!remove_special_chars(ptr))
				return (0);
		}
		list = list->next;
	}
	return (1);
}

int	check_if_var_is_not_exist(t_input *input, t_input *head, int i, int x)
{
	while (input)
	{
		if (input->cmd_av)
		{
			i = -1;
			while (input->cmd_av[++i])
			{
				if (only_special_chars(input->cmd_av[i]))
				{
					x = -1;
					while (input->cmd_av[i][++x])
						input->cmd_av[i][x] = 0;
				}
				else if (special_and_normale_chars(input->cmd_av[i]))
				{
					if (!remove_special_chars(&(input->cmd_av[i])))
						return (0);
				}
			}
		}
		if (!check_for_list(input->list))
			return (0);
		input = input->next;
	}
	return (swap_args(head), 1);
}

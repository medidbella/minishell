/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:29:08 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/14 12:54:47 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_infos(char *str, int i, t_expnd *expnd, t_list *env)
{
	int		x;
	char	*search_var;
	int		j;

	j = 0;
	expnd->var_len = 0;
	x = (i + 1);
	expnd->var_len++;
	if (str[i + 1] == '?')
		i += 2;
	else
	{
		while (str[++i] && str[i] != ' ' && str[i] != S_QUOTES && str[i]
			!= D_QUOTES && str[i] != SPACES && str[i] != DOLLAR
			&& str[i] != '$' && str[i] != REMOVE)
			expnd->var_len++;
	}
	search_var = malloc(sizeof(char) * (expnd->var_len + 2));
	if (!search_var)
		return (-1);
	expnd->var = malloc(sizeof(char) * (expnd->var_len + 2));
	if (!expnd->var)
		return (-1);
	get_infos_2(expnd, str, search_var, x);
	return (ft_infos(env, expnd, search_var), free(search_var), i);
}

int	get_value(int value_len, char *value, char *new_str, int *x)
{
	int	i;

	i = 0;
	while (value[i] != '=')
		i++;
	i++;
	while (value[i])
	{
		new_str[*x] = value[i];
		(*x)++;
		i++;
	}
	return (ft_strlen(value) - value_len);
}

char	*ft_compensation(char *curr_str, char *new_str, t_expnd *expnd, int i)
{
	t_expnd	*head;
	int		x;
	int		y;

	head = expnd;
	x = 0;
	while (curr_str[i])
	{
		y = 0;
		if (curr_str[i] == '$' && curr_str[i + 1] && curr_str[i + 1] != ' ')
		{
			if (expnd->exist)
				i += get_value(expnd->value_len, expnd->env->content,
						new_str, &x);
			else
				i += if_not_exists(expnd, new_str, &x);
			expnd = expnd->next;
		}
		else
			new_str[x++] = curr_str[i++];
	}
	new_str[x] = 0;
	free_expnd(head);
	return (free(curr_str), new_str);
}

char	*ft_expansion(char *str, t_list *env, int i, t_expnd *expnd)
{
	t_expnd	*new_expnd;
	int		len;
	char	*new_str;

	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1]
			!= ' ')
		{
			new_expnd = ft_lst_new();
			if (!new_expnd)
				return (free_expnd(expnd), NULL);
			i = get_infos(str, i, new_expnd, env);
			if (i == -1)
				return (free_expnd(expnd), NULL);
			ft_lst_add_back(&expnd, new_expnd);
		}
		else
			i++;
	}
	len = get_the_len(expnd, ft_strlen(str));
	new_str = malloc(sizeof(char) * len);
	if (!new_str)
		return (free_expnd(expnd), NULL);
	return (ft_compensation(str, new_str, expnd, 0));
}

int	expansion(t_input *input, t_list *env, int i)
{
	t_options	*list;
	t_input		*head;
	char		*new_cmd_av;

	head = input;
	while (input)
	{
		i = -1;
		if (input->cmd_av)
		{
			while (input->cmd_av[++i])
			{
				new_cmd_av = ft_expansion(input->cmd_av[i], env, 0, NULL);
				if (!new_cmd_av)
					return (0);
				input->cmd_av[i] = new_cmd_av;
			}
		}
		list = input->list;
		if (!expansion_for_list(list, env))
			return (0);
		input = input->next;
	}
	return (check_if_var_is_not_exist(head, head, 0, 0));
}

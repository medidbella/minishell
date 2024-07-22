/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:29:08 by alaktari          #+#    #+#             */
/*   Updated: 2024/07/22 10:42:07 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_infos(char *read_line, int i, t_expnd *expnd, t_list *env)
{
	int		x;
	int		y;
	char	*var;
	int		j;

	y = 0;
	j = 0;
	expnd->var_len = 0;
	x = (i + 2);
	while (read_line[++i] && read_line[i] != ' ')
		expnd->var_len++;
	var = malloc(sizeof(char) * (expnd->var_len + 2));
	if (!var)
		return (-1);
	expnd->var = malloc(sizeof(char) * (expnd->var_len + 2));
	if (!expnd->var)
		return (-1);
	get_infos_2(expnd, read_line, var, x);
	return (ft_infos(env, expnd, var), free(var), i);
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

char	*ft_compensation(char *read_line, char *new_str, t_expnd *expnd, int i)
{
	int		x;
	int		y;
	int		j;

	x = 0;
	j = 0;
	while (read_line[i])
	{
		y = 0;
		if (read_line[i] == '$' && read_line[i + 1] && read_line[i + 1] != ' ')
		{
			if (expnd->exist)
				i += get_value(expnd->value_len, expnd->env->content,
						new_str, &x);
			else
				i += if_not_exists(expnd, new_str, &j, &x);
			expnd = expnd->next;
		}
		else
			new_str[x++] = read_line[i++];
	}
	return (new_str[x] = 0, free(read_line), new_str);
}

char	*ft_expansion(char *read_line, t_list *env, int i, t_expnd *expnd)
{
	t_expnd	*new_expnd;
	int		len;
	char	*new_str;

	while (read_line[i])
	{
		if (read_line[i] == '$' && read_line[i + 1] && read_line[i + 1]
			!= ' ')
		{
			new_expnd = ft_lst_new();
			if (!new_expnd)
				return (NULL);
			i = get_infos(read_line, (i - 1), new_expnd, env);
			if (i == -1)
				return (NULL);
			ft_lst_add_back(&expnd, new_expnd);
		}
		else
			i++;
	}
	len = get_the_len(expnd, ft_strlen(read_line));
	new_str = malloc(sizeof(char) * len);
	if (!new_str)
		return (NULL);
	return (ft_compensation(read_line, new_str, expnd, 0));
}

int	expansion(t_input *input, t_list *env, int i)
{
	t_options	*list;

	while (input)
	{
		i = -1;
		if (input->cmd_av)
		{
			while (input->cmd_av[++i])
			{
				input->cmd_av[i] = ft_expansion(input->cmd_av[i], env, 0, NULL);
				if (!(input->cmd_av[i]))
					return (0);
			}
		}
		list = input->list;
		if (!expansion_for_list(list, env))
			return (0);
		input = input->next;
	}
	return (1);
}

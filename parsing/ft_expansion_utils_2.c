/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:42:59 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/22 17:44:53 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_infos_2(t_expnd *expnd, char *str, char *search_var, int x)
{
	int	j;
	int	y;

	j = 0;
	y = 0;
	expnd->var[j++] = '$';
	while (str[x] && str[x] != ' ' && str[x] != S_QUOTES
		&& str[x] != D_QUOTES && str[x] != DOLLAR
		&& str[x] != SPACES && str[x] != '$' && str[x] != REMOVE
		&& limiter_chars(str[x]))
	{
		expnd->var[j++] = str[x];
		search_var[y++] = str[x++];
	}
	search_var[y++] = '=';
	search_var[y] = 0;
	expnd->var[j] = 0;
}

int	expansion_for_list(t_options *list, t_list *env)
{
	char	**ptr_to;
	char	*new_str;

	while (list)
	{
		if (list->input)
			ptr_to = &list->input;
		else if (list->out)
			ptr_to = &list->out;
		else
		{
			list = list->next;
			continue ;
		}
		new_str = ft_expansion(*ptr_to, env, 0, NULL);
		if (!new_str)
			return (0);
		*ptr_to = new_str;
		list = list->next;
	}
	return (1);
}

int	if_not_exists(t_expnd *expnd, char *new_str, int *x)
{
	int	i;

	i = 0;
	while (expnd->var[i++])
		new_str[(*x)++] = NOT_EXIST;
	return (expnd->var_len);
}

void	ft_cpy(char *splited, int *i, char *str, int *x)
{
	while (splited[*i] && splited[*i] != ' ' && splited[*i] != '>'
		&& splited[*i] != '<')
	{
		str[(*x)++] = splited[*i];
		splited[(*i)++] = ' ';
	}
	str[(*x)++] = 0;
}

void	no_expand(char **ptr)
{
	int	i;

	i = 0;
	while ((*ptr)[i])
	{
		if ((*ptr)[i] == EXIT_STATUS)
		{
			(*ptr)[i++] = '$';
			(*ptr)[i] = '?';
		}
		i++;
	}
	i = -1;
	while ((*ptr)[++i])
		replace_special_chars(&((*ptr)[i]));
}

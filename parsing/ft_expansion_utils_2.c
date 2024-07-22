/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:42:59 by alaktari          #+#    #+#             */
/*   Updated: 2024/07/22 10:42:07 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_infos_2(t_expnd *expnd, char *read_line, char *var, int x)
{
	int	j;
	int	y;

	j = 0;
	y = 0;
	expnd->var[j++] = '$';
	while (read_line[x] && read_line[x] != ' ')
	{
		expnd->var[j++] = read_line[x];
		var[y++] = read_line[x++];
	}
	var[y++] = '=';
	var[y] = 0;
	expnd->var[j] = 0;
}

int	expansion_for_list(t_options *list, t_list *env)
{
	char	**ptr_to;

	while (list)
	{
		if (list->input)
			ptr_to = &list->input;
		else if (list->limiter)
			ptr_to = &list->limiter;
		else if (list->out)
			ptr_to = &list->out;
		*ptr_to = ft_expansion(*ptr_to, env, 0, NULL);
		if (!(*ptr_to))
			return (0);
		list = list->next;
	}
	return (1);
}

int	if_not_exists(t_expnd *expnd, char *new_str, int *j, int *x)
{
	while (expnd->var[*j])
		new_str[(*x)++] = expnd->var[(*j)++];
	return (expnd->var_len);
}

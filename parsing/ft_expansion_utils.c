/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:01:03 by alaktari          #+#    #+#             */
/*   Updated: 2024/07/22 10:42:07 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expnd	*ft_lst_new(void)
{
	t_expnd	*the_new_node;

	the_new_node = malloc(sizeof(t_expnd));
	if (!the_new_node)
		return (NULL);
	the_new_node -> next = NULL;
	return (the_new_node);
}

t_expnd	*ft_lst_last(t_expnd *lst)
{
	while (lst)
	{
		if (!lst -> next)
			return (lst);
		lst = lst -> next;
	}
	return (lst);
}

void	ft_lst_add_back(t_expnd **lst, t_expnd *new)
{
	t_expnd	*mlst;

	if (lst && new)
	{
		if (*lst)
		{
			mlst = ft_lst_last(*lst);
			mlst -> next = new;
		}
		else
			*lst = new;
	}
}

int	get_the_len(t_expnd *expnd, int read_line_len)
{
	int	len;
	int	vars_len;
	int	values_len;

	values_len = 0;
	vars_len = 0;
	while (expnd)
	{
		if (expnd->exist)
		{
			vars_len += expnd->var_len;
			values_len += expnd->value_len;
		}
		expnd = expnd->next;
	}
	len = read_line_len - vars_len + values_len + 1;
	return (len);
}

void	ft_infos(t_list *env, t_expnd *expnd, char *var)
{
	while (env)
	{
		if (!strncmp(env->content, var, expnd->var_len))
		{
			expnd->env = env;
			expnd->value_len = ft_strlen(env->content) - expnd->var_len;
			expnd->exist = 1;
			return ;
		}
		env = env->next;
	}
	expnd->exist = 0;
	expnd->env = NULL;
	return ;
}

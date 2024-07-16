/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:21:09 by midbella          #+#    #+#             */
/*   Updated: 2024/07/07 16:09:41 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_node(t_list **head, int index)
{
	t_list	*tmp;
	t_list	*iter;
	int		i;

	i = 0;
	tmp = *head;
	iter = *head;
	if (index == 0)
	{
		tmp = tmp->next;
		free((*head)->content);
		free(*head);
		*head = tmp;
		return ;
	}
	while (i != index - 1 && iter)
	{
		iter = iter->next;
		i++;
	}
	tmp = iter->next;
	iter->next = tmp->next;
	return (free(tmp->content), free(tmp));
}

int	name_cmp(char *env_var, char *var)
{
	int	i;

	i = 0;
	while (var[i] == env_var[i] && var[i] && env_var[i] && env_var[i] != '=')
		i++;
	if (i == ft_strlen(var) && (env_var[i] == '=' || env_var[i] == 0))
		return (1);
	else
		return (0);
}

int	ft_unset(t_input *data, t_list **env)
{
	char	*err_msg;
	t_list	*iter;
	int		i;
	int		index;

	i = 0;
	err_msg = ("minishell: unset: no option is supported");
	if (data->cmd_av[1][0] == '-')
		return (print_error(ft_strdup(err_msg)), 2);
	while (data->cmd_av[++i])
	{
		index = 0;
		iter = *env;
		while (iter)
		{
			if (name_cmp(iter->content, data->cmd_av[i]))
			{
				del_node(env, index);
				break ;
			}
			index++;
			iter = iter->next;
		}
	}
	return (0);
}

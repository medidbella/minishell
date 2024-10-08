/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:50:54 by midbella          #+#    #+#             */
/*   Updated: 2024/08/24 16:03:48 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_listdup(t_list *list)
{
	t_list	*head;
	t_list	*iter;

	if (!list)
		return (NULL);
	head = ft_lstnew(ft_strdup(list->content));
	iter = head;
	list = list->next;
	while (list)
	{
		iter->next = ft_lstnew(ft_strdup(list->content));
		iter = iter->next;
		list = list->next;
	}
	return (head);
}

int	sort_helper(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] == str2[i] && str1[i] != '='
		&& str2[i] != '=')
		i++;
	if (str1[i] != '=' && str2[i] != '=' && str1[i] > str2[i])
		return (1);
	else if (str2[i] == '=' && str1[i] != '=')
		return (1);
	return (0);
}

void	swap_str(char **str1, char **str2, int *flag)
{
	char	*tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
	*flag = 1;
}

int	is_optoin(char *arg)
{
	int	i;

	i = 1;
	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	inputs_count(t_input *inpt_list)
{
	int	i;

	i = 0;
	while (inpt_list)
	{
		i++;
		inpt_list = inpt_list->next;
	}
	return (i);
}

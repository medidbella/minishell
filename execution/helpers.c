/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:50:54 by midbella          #+#    #+#             */
/*   Updated: 2024/07/06 14:34:50 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_listdup(t_list *list)
{
	t_list	*head;
	t_list	*iter;

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

void	lst_free(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->content);
		free(list);
		list = tmp;
	}
}

void	swap_str(char **str1, char **str2, int *flag)
{
	char	*tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
	*flag = 1;
}

void	printer(t_list *head)
{
	int	flag;
	int	index;

	while (head)
	{
		flag = 0;
		index = 0;
		printf("declare -x ");
		while (head->content[index])
		{
			if (index && head->content[index] == '=' && flag == 0)
			{
				printf("=%c", '"');
				flag = 1;
			}
			else
				printf("%c", head->content[index]);
			index++;
		}
		if (flag == 1)
			printf("%c", '"');
		printf("\n");
		head = head->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:47:46 by alaktari          #+#    #+#             */
/*   Updated: 2024/07/22 10:42:07 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lstsize(t_options *lst)
{
	int		len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst -> next;
	}
	return (len);
}

t_options	*lstlast(t_options *lst)
{
	while (lst)
	{
		if (!lst -> next)
			return (lst);
		lst = lst -> next;
	}
	return (lst);
}

void	lstadd_back(t_options **lst, t_options *new_node)
{
	t_options	*mlst;

	if (lst && new_node)
	{
		if (*lst)
		{
			mlst = lstlast(*lst);
			mlst -> next = new_node;
		}
		else
			*lst = new_node;
	}
}

t_input	*lst_last(t_input *head)
{
	while (head)
	{
		if (!head -> next)
			return (head);
		head = head -> next;
	}
	return (head);
}

void	lstadd__back(t_input **input, t_input *new_node)
{
	t_input	*mlst;

	if (input && new_node)
	{
		if (*input)
		{
			mlst = lst_last(*input);
			mlst -> next = new_node;
		}
		else
			*input = new_node;
	}
}

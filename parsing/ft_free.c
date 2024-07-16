/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:09:41 by alaktari          #+#    #+#             */
/*   Updated: 2024/07/12 21:50:44 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_splited(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
		free(splited[i++]);
	free(splited);
}

void	free_list(t_options *list)
{
	t_options	*next;

	while (list)
	{
		next = list->next;
		free(list);
		list = next;
	}
}

void	free_t_inputs(t_input *head)
{
	t_input	*next;

	while (head)
	{
		next = head->next;
		free_splited(head->cmd_av);
		if (head->list)
			free_list(head->list);
		free(head);
		head = next;
	}
}

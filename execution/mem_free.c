/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:21:23 by midbella          #+#    #+#             */
/*   Updated: 2024/08/24 16:04:59 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_strings(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	lstfree(t_list *list)
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

void	child_mem_free(t_holder *mem, char **child_env)
{
	free(child_env);
	free_inputs(mem->input_head);
	lstfree(mem->env);
	rl_clear_history();
	close_and_free_pipes(mem->pipes);
}

void	init_vars(int *a, int *b, int *c)
{
	*a = -1;
	*b = -1;
	*c = -1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_args_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:34:20 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/17 15:37:40 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_empty_strs(t_input *input)
{
	int	i;

	i = 0;
	if (input->cmd_av)
	{
		while (input->cmd_av[i] && input->cmd_av[i][0])
			i++;
		if (input->cmd_av[i])
		{
			while (input->cmd_av[i])
			{
				free(input->cmd_av[i]);
				input->cmd_av[i] = NULL;
				i++;
			}
		}
	}
}

void	check_list(t_options *list)
{
	char	**p_to;

	if (!list)
		return ;
	p_to = NULL;
	if (list->input)
		p_to = &(list->input);
	else if (list->out)
		p_to = &(list->out);
	else if (list->limiter)
		p_to = &(list->limiter);
	else
		return ;
	if (!(*p_to)[0])
	{
		free(*p_to);
		*p_to = NULL;
	}
}

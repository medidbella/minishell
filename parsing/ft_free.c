/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:09:41 by alaktari          #+#    #+#             */
/*   Updated: 2024/07/22 10:42:07 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_inputs(t_input *input)
{
	int			i;
	int			x;
	t_options	*next;
	t_input		*next_input;

	i = 0;
	x = 0;
	while (input)
	{
		while (input->cmd_av[i])
			free(input->cmd_av[i++]);
		while (input->list)
		{
			free(input->list->input);
			free(input->list->out);
			free(input->list->limiter);
			next = input->list->next;
			free(input->list);
			input->list = next;
		}
		next_input = input->next;
		free(input);
		input = next_input;
	}
}

void	free_splited(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
		free(splited[i++]);
	free(splited);
}

void	free_expnd(t_expnd *expnd)
{
	t_expnd	*next;

	while (expnd)
	{
		next = expnd->next;
		free(expnd->var);
		free(expnd);
		expnd = next;
	}
}

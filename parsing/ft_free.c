/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 10:09:41 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/14 12:54:47 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_list_in_struct(t_options *list)
{
	t_options	*next;

	while (list)
	{
		free(list->input);
		free(list->out);
		free(list->limiter);
		next = list->next;
		free(list);
		list = next;
	}
}

void	free_inputs(t_input *input)
{
	int			i;
	t_input		*next_input;

	while (input)
	{
		if (input->cmd_av)
		{
			i = 0;
			while (input->cmd_av[i])
				free(input->cmd_av[i++]);
			free(input->cmd_av);
		}
		free_list_in_struct(input->list);
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

void	free_env(t_list *env)
{
	t_list	*next;

	while (env)
	{
		next = env->next;
		free(env->content);
		free(env);
		env = next;
	}
}

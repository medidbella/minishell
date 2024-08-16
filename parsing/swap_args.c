/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 00:11:45 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/14 12:54:47 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_to_bottom(char **cmd_av, int index)
{
	char	*swaper;

	while (cmd_av[index])
	{
		if (cmd_av[index + 1])
		{
			swaper = cmd_av[index];
			cmd_av[index] = cmd_av[index + 1];
			cmd_av[index + 1] = swaper;
		}
		index++;
	}
	free(cmd_av[index - 1]);
	cmd_av[index - 1] = NULL;
}

int	no_more_swap(char **cmd_av, int i)
{
	int	checker_1;
	int	checker_2;

	checker_1 = 0;
	checker_2 = 0;
	while (cmd_av[++i])
	{
		if (!cmd_av[i][0])
		{
			checker_1 = 1;
			break ;
		}
	}
	while (cmd_av[i])
	{
		if (cmd_av[i][0])
		{
			checker_2 = 1;
			break ;
		}
		i++;
	}
	if (checker_1 && checker_2)
		return (0);
	return (1);
}

int	only_empty_strs(char **cmd_av)
{
	int	i;

	i = 0;
	while (cmd_av[i])
	{
		if (cmd_av[i][0])
			return (0);
		i++;
	}
	return (1);
}

void	check_cmd_av(t_input *input)
{
	if (input->cmd_av)
	{
		if (only_empty_strs(input->cmd_av))
		{
			free_splited(input->cmd_av);
			input->cmd_av = NULL;
		}
	}
}

void	swap_args(t_input *input)
{
	int	i;

	while (input)
	{
		if (input->cmd_av)
		{
			i = 0;
			while (input->cmd_av[i])
			{
				if (no_more_swap(input->cmd_av, -1))
					break ;
				if (!input->cmd_av[i][0])
					swap_to_bottom(input->cmd_av, i);
				else
					i++;
			}
		}
		check_cmd_av(input);
		free_empty_strs(input);
		check_list(input->list);
		input = input->next;
	}
}

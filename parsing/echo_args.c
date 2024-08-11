/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:41:58 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/08 15:32:45 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	get_new_arg(char *new_arg, char **splited_arg)
{
	int	i;
	int	x;
	int	j;

	i = 0;
	j = 0;
	while (splited_arg[i])
	{
		x = 0;
		while (splited_arg[i][x])
			new_arg[j++] = splited_arg[i][x++];
		if (splited_arg[i + 1])
			new_arg[j++] = ' ';
		i++;
	}
	new_arg[j] = 0;
}

char	*get_splited_arg(char *arg)
{
	char	**splited_arg;
	char	*new_arg;
	int		len;

	tabs_to_spaces(arg);
	splited_arg = ft_split(arg, ' ');
	if (!splited_arg)
		return (NULL);
	len = len_of_splited_arg(splited_arg);
	new_arg = malloc(sizeof(char) * len);
	if (!new_arg)
		return (free_splited(splited_arg), NULL);
	get_new_arg(new_arg, splited_arg);
	return (free_splited(splited_arg), free(arg), new_arg);
}

static int	get_the_new_argument(char **cmd_av)
{
	char	*new_arg;
	int		i;

	i = 1;
	while (cmd_av[i])
	{
		if (cmd_av[i][0] != REMOVE)
		{
			new_arg = get_splited_arg(cmd_av[i]);
			if (!new_arg)
				return (0);
			cmd_av[i] = new_arg;
		}
		i++;
	}
	return (1);
}

int	skip_spaces_for_echo_args(t_input *input)
{
	t_input	*head;

	head = input;
	while (input)
	{
		if (input->cmd_av)
		{
			if (input->type == BUILTIN && !ft_strncmp(input->cmd_av[0],
					"echo", 5))
			{
				if (!get_the_new_argument(input->cmd_av))
					return (0);
			}
		}
		input = input->next;
	}
	remove_quotes(head);
	return (1);
}

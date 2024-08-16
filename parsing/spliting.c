/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:41:58 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/14 12:54:47 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_built_in(t_input	*input)
{
	int		len;
	char	*cmd;

	while (input)
	{
		if (input->cmd_av && input->cmd_av[0])
		{
			cmd = input->cmd_av[0];
			len = ft_strlen(cmd);
			if (((!ft_strncmp(cmd, "echo", len) && len == 4))
				|| ((!ft_strncmp(cmd, "pwd", len)) && len == 3)
				|| ((!ft_strncmp(cmd, "export", len)) && len == 6)
				|| ((!ft_strncmp(cmd, "unset", len)) && len == 5)
				|| ((!ft_strncmp(cmd, "exit", len)) && len == 4)
				|| ((!ft_strncmp(cmd, "env", len)) && len == 3)
				|| ((!ft_strncmp(cmd, "cd", len)) && len == 2))
				input->type = BUILTIN;
			else
				input->type = EXTERNAL;
		}
		input = input->next;
	}
	return (1);
}

static int	get_cmd_av_size(char **cmd_av)
{
	int	size;

	size = 0;
	while (cmd_av[size])
		size++;
	return (size);
}

static int	new_cmd_av(char ***old, int index, int size, char **splited)
{
	int		i;
	int		x;
	char	**new;
	int		splited_size;
	int		new_size;

	i = 0;
	x = -1;
	splited_size = get_cmd_av_size(splited);
	new_size = size + splited_size;
	new = malloc(sizeof(char *) * new_size);
	if (!new)
		return (0);
	while (++x < index)
		new[x] = (*old)[x];
	while (splited[i])
		new[x++] = splited[i++];
	free((*old)[index++]);
	while ((*old)[index])
		new[x++] = (*old)[index++];
	new[x] = NULL;
	free(splited);
	free(*old);
	(*old) = new;
	return (1);
}

int	no_remove(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == REMOVE)
			return (0);
		i++;
	}
	return (1);
}

int	split_cmds_and_args(t_input *input, t_input *head, int i)
{
	int		size;
	char	**splited;

	while (input)
	{
		if (input->cmd_av)
		{
			i = -1;
			while (input->cmd_av[++i])
			{
				if (no_remove(input->cmd_av[i]))
				{
					size = get_cmd_av_size(input->cmd_av);
					tabs_to_spaces(input->cmd_av[i], -1);
					splited = ft_split(input->cmd_av[i], ' ');
					if (!splited)
						return (0);
					if (!new_cmd_av(&(input->cmd_av), i, size, splited))
						return (0);
				}
			}
		}
		input = input->next;
	}
	return (remove_quotes(head, head));
}

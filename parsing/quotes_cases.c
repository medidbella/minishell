/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:37:16 by alaktari          #+#    #+#             */
/*   Updated: 2024/07/12 21:51:18 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	case_of_pipe_inside_quotes_1(char *read_line)
{
	int	i;

	i = -1;
	while (read_line[++i])
	{
		if (read_line[i] == '"')
		{
			while (read_line[++i] != '"')
			{
				if (read_line[i] == '|')
					read_line[i] = -1;
			}
		}
		else if (read_line[i] == 39)
		{
			while (read_line[++i] != 39)
			{
				if (read_line[i] == '|')
					read_line[i] = -1;
			}
		}
	}
}


void	case_of_pipe_inside_quotes_2(char **splited)
{
	int	i;
	int	x;

	i = -1;
	while (splited[++i])
	{
		x = -1;
		while (splited[i][++x])
		{
			if (splited[i][x] == -1)
				splited[i][x] = '|';
		}
	}
}

int	remove_double_quotes(char **cmd_av, int i)
{
	int		x;
	char	*new_str;
	int		y;

	i = -1;
	while (cmd_av[++i])
	{
		x = 0;
		y = 0;
		if (cmd_av[i][0] == '"')
		{
			new_str = malloc(sizeof(char) * (ft_strlen(cmd_av[i]) - 1));
			if (!new_str)
				return (0);
			while (cmd_av[i][++x])
			{
				if (cmd_av[i][x] != '"')
					new_str[y++] = cmd_av[i][x];
			}
			new_str[y] = '\0';
			free(cmd_av[i]);
			cmd_av[i] = new_str;
		}
	}
	return (1);
}

void	case_of_spaces_inside_double_quotes_1(char *s2)
{
	int	i;

	i = -1;
	while (s2[++i])
	{
		if (s2[i] == '"')
		{
			while (s2[++i] != '"')
			{
				if (s2[i] == ' ')
					s2[i] = -1;
			}
		}
	}
}

void	case_of_spaces_inside_double_quotes_2(char **cmd_av)
{
	int	i;
	int	x;

	i = -1;

	while (cmd_av[++i])
	{
        x = -1;
        while (cmd_av[i][++x])
        {
            if (cmd_av[i][x] == -1)
                cmd_av[i][x] = ' ';
        }
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_cases_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:43:31 by alaktari          #+#    #+#             */
/*   Updated: 2024/07/12 21:51:15 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_there_single_quotes(char *splited)
{
	int i;

	i = -1;
	while (splited[++i])
	{
		if (splited[i] == '"')
		{
			i++;
			while (splited[i] != '"')
				i++;
		}
		if (splited[i] == 39)
			return (1);
	}
	return (0);
}

int	remove_single_quotes(char **splited, int i, int x, int y)
{
	char *new_str;

	while (splited[++i])
	{
		if (!is_there_single_quotes(splited[i]))
			continue ;
		x = -1;
		y = 0;
		while (splited[i][++x])
				y++;
		new_str = malloc(sizeof(char) * (y - 1));
		if (!new_str)
			return (0);
		x = -1;
		y = 0;
		while (splited[i][++x])
		{
			if (splited[i][x] != 39)
				new_str[y++] = splited[i][x];
		}
		new_str[y] = '\0';
		free(splited[i]);
		splited[i] = new_str;
	}
	return (1);
}

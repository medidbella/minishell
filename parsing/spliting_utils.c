/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 04:26:34 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/17 16:00:25 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_remove(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == REMOVE)
			return (0);
		i++;
	}
	return (1);
}

int	get_cmd_av_size(char **cmd_av)
{
	int	size;

	size = 0;
	while (cmd_av[size])
		size++;
	return (size);
}

int	more_than_a_word(char *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ' && (str[i + 1] == ' ' || !str[i + 1]))
			words++;
		if (words > 1)
			return (1);
		i++;
	}
	return (0);
}

int	get_the_new_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			len++;
		i++;
	}
	return (len);
}

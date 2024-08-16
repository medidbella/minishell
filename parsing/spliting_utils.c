/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 04:26:34 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/14 12:54:47 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tabs_to_spaces(char *arg, int i)
{
	while (arg[++i])
	{
		if (arg[i] == '"')
		{
			i++;
			while (arg[i] != '"' && arg[i])
			{
				if (arg[i] == '\t' || arg[i] == ' ')
					arg[i] = SPACES;
				i++;
			}
		}
		else if (arg[i] == 39)
		{
			i++;
			while (arg[i] != 39 && arg[i])
			{
				if (arg[i] == '\t' || arg[i] == ' ')
					arg[i] = SPACES;
				i++;
			}
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_args_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:34:53 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/08 15:37:23 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tabs_to_spaces(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\t')
			arg[i] = ' ';
		i++;
	}
}

int	len_of_splited_arg(char **splited_arg)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (splited_arg[i])
	{
		len += ft_strlen(splited_arg[i]);
		len++;
		i++;
	}
	return (len);
}

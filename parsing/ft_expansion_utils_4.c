/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_utils_4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:58:43 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/20 16:39:55 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	limiter_chars(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	ft_specials(char c, int who)
{
	if (who == 1)
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')
			|| (c >= '0' && c <= '9'))
			return (0);
	}
	else
	{
		if (c < '0' || c > '9')
			return (0);
	}
	return (1);
}

void	there_are_specials(char *str, int i)
{
	if (str[i] == '$' && ft_specials(str[i + 1], 1) && str[i + 1])
		str[i] = DOLLAR;
	else if (str[i] == '$' && str[i + 1] && ft_specials(str[i + 1], 2))
	{
		str[i++] = REMOVE;
		str[i] = REMOVE;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:06:50 by midbella          #+#    #+#             */
/*   Updated: 2023/11/24 17:41:37 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	char			*ptr;

	ptr = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
		{
			ptr = (char *)&s[i];
			break ;
		}
		i++;
	}
	if (s[i] == (char)c)
		ptr = (char *)&s[i];
	return (ptr);
}

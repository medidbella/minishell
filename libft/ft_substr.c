/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 23:04:09 by midbella          #+#    #+#             */
/*   Updated: 2023/11/23 11:17:12 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*sub;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		sub = malloc(sizeof(char) * 1);
		if (sub == NULL )
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (len >= ft_strlen(&s[start]))
		sub = malloc(sizeof(char) * ft_strlen(&s[start]) + 1);
	else
		sub = malloc(sizeof(char) * len + 1);
			i = 0;
	if (sub == NULL)
		return (NULL);
	while (s[start] && len-- > 0)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

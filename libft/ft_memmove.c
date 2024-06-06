/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:40:26 by midbella          #+#    #+#             */
/*   Updated: 2023/11/21 19:52:58 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*de;
	const char	*sr;
	size_t		i;

	i = 0;
	de = (char *)dst;
	sr = (const char *)src;
	if (!dst && !src)
		return (dst);
	if (dst < src)
	{
		while (i < len)
		{
			de[i] = sr[i];
			i++;
		}
	}
	else if (dst > src)
	{
		while (len--)
			de[len] = sr[len];
	}
	return (dst);
}

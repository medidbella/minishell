/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:57:36 by midbella          #+#    #+#             */
/*   Updated: 2023/11/26 14:16:02 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*ptr1;
	const char	*ptr2;

	if (dst == NULL && src == NULL )
		return (NULL);
	if (dst == src)
		return (dst);
	i = 0;
	ptr1 = (char *) dst;
	ptr2 = (const char *) src;
	while (n > 0)
	{
		ptr1[i] = ptr2[i];
		i++;
		n--;
	}
	return (dst);
}

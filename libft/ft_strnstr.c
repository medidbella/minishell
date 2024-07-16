/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:47:26 by midbella          #+#    #+#             */
/*   Updated: 2024/07/15 17:47:29 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	h;
	size_t	n;

	n = ft_strlen(needle);
	h = ft_strlen(haystack);
	i = 0;
	if (needle[0] == '\0' || needle == NULL)
		return ((char *) haystack);
	if (n > len || haystack == NULL || n > h)
		return (NULL);
	while (i < len && haystack[i] && n + i <= len)
	{
		if (ft_strncmp(&haystack[i], needle, n) == 0)
			return ((char *) &haystack[i]);
		i++;
	}
	return (NULL);
}

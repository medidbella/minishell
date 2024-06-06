/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:15:41 by midbella          #+#    #+#             */
/*   Updated: 2023/11/23 22:09:45 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strjoin(char const *s1, char const *s2)
{
	size_t ls1;
	size_t ls2;
	char *res;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	res = malloc(sizeof(char) * (ls1 + ls2 + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, ls1 + 1);
	ft_strlcat(res, s2, ls2 + ls1 + 1);
	return (res);
}

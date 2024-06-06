/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:49:44 by midbella          #+#    #+#             */
/*   Updated: 2023/11/26 13:02:46 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*max_int(void)
{
	size_t	i;
	char	*max;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * 12);
	if (!str)
		return (NULL);
	max = "-2147483648";
	while (max[i])
	{
		str[i] = max[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static size_t	total_len(int n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		i = 2;
		n = n * -1;
	}
	if (n < 10 && n >= 0)
		return (i);
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*str;

	if (n == -2147483648)
		return (max_int());
	len = total_len(n);
	str = malloc(sizeof (char) * len + 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	str[len] = '\0';
	len--;
	while (n >= 10)
	{
		str[len--] = (n % 10) + 48;
		n = n / 10;
	}
	str[len] = n + 48;
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:27:01 by midbella          #+#    #+#             */
/*   Updated: 2023/11/25 17:40:31 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	s[10];
	int		j;

	if (fd < 0)
		return ;
	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
			nb = nb * -1;
	}
	j = 0;
	while (nb >= 10)
	{
		s[j] = (nb % 10) + 48;
		nb = nb / 10;
		j++;
	}
	s[j] = nb + 48;
	while (j >= 0)
	{
		write(fd, &s[j], 1);
		j--;
	}
}

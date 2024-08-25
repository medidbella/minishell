/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:21:45 by midbella          #+#    #+#             */
/*   Updated: 2024/08/24 18:24:06 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	custome_strlen(char *str)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (str[j] == '0')
		j++;
	while (str[j])
	{
		i++;
		j++;
	}
	return (i);
}

int	limiter_check(char *str)
{
	int		i;
	size_t	result;
	int		sign;

	if (custome_strlen(str) > 19)
		return (1);
	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result > 9223372036854775807);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (limiter_check(str))
		return (0);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !(i == 0 && ft_isdigit(str[i + 1])
				&& (str[i] == '+' || str[i] == '-')))
			return (0);
		i++;
	}
	return (1);
}

void	log_msg(char *dir, int write_fd)
{
	if (write_fd == -1)
		write_fd = 1;
	if (is_dir(dir))
		ft_putendl_fd(dir, write_fd);
	return ;
}

void	ft_close(int fd)
{
	if (fd >= 0)
		close(fd);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:54:54 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/14 12:54:47 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_sig	*g_status;

static int	there_is_exit_status(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == EXIT_STATUS)
			return (1);
		i++;
	}
	return (0);
}

int	number_of_digits(int digit)
{
	int	digit_num;

	digit_num = 0;
	if (digit == 0)
		return (1);
	else
	{
		while (digit)
		{
			digit_num++;
			digit /= 10;
		}
	}
	return (digit_num);
}

int	get_vars_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == EXIT_STATUS)
			len++;
		i++;
	}
	return (len);
}

static void	f_t_copy(char *curr_str, char *new_str, char *value)
{
	int	i;
	int	x;
	int	j;

	i = 0;
	x = 0;
	while (curr_str[i])
	{
		if (curr_str[i] == EXIT_STATUS)
		{
			j = 0;
			while (value[j])
				new_str[x++] = value[j++];
			i += 2;
		}
		else
			new_str[x++] = curr_str[i++];
	}
	new_str[x] = 0;
}

char	*get_return_value(char *curr_str)
{
	int		vars_len;
	int		values_len;
	char	*new_str;
	char	*value;

	if (there_is_exit_status(curr_str))
	{
		vars_len = get_vars_len(curr_str);
		values_len = (number_of_digits(g_status->r_val)) * (vars_len / 2);
		value = ft_itoa(g_status->r_val);
		if (!value)
			return (NULL);
		vars_len = ft_strlen(curr_str) - vars_len + values_len + 1;
		new_str = malloc(sizeof(char) * vars_len);
		if (!new_str)
			return (free(value), NULL);
		f_t_copy(curr_str, new_str, value);
		return (free(curr_str), free(value), new_str);
	}
	return (curr_str);
}

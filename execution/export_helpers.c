/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:46:48 by midbella          #+#    #+#             */
/*   Updated: 2024/07/21 13:17:50 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	double_quotes(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
		if (str[i++] == '"')
			count++;
	if (count % 2 != 0)
		return (0);
	else
		return (1);
}

void	printer(t_list *head, int write_fd)
{
	int	flag;
	int	index;

	while (head)
	{
		flag = 0;
		index = 0;
		ft_putstr_fd("declare -x ", write_fd);
		while (head->content[index])
		{
			if (index && head->content[index] == '=' && flag == 0)
			{
				ft_putchar_fd('=', write_fd);
				ft_putchar_fd('"', write_fd);
				flag = 1;
			}
			else
				ft_putchar_fd(head->content[index], write_fd);
			index++;
		}
		if (flag == 1)
			ft_putchar_fd('"', write_fd);
		ft_putchar_fd('\n', write_fd);
		head = head->next;
	}
}

void	error_detector(char *av, int *return_val)
{
	char	*tmp;

	*return_val = 0;
	while (av[*return_val] && av[*return_val] != '+')
		*return_val += 1;
	if (!ft_isalpha(av[0]) && av[0] != '"' || av[*return_val] == '+'
		&& av[*return_val + 1] != '=')
	{
		tmp = ft_strjoin("minishell: export:`", av);
		print_error(ft_strjoin(tmp, "':not a valid indentifier"));
		av[0] = 0;
		*return_val = 1;
		return (free(tmp));
	}
	else if (!double_quotes(av))
	{
		*return_val = 1;
		av[0] = 0;
	}
}

int	var_finder(t_list *env, char *var)
{
	char	*res;
	int		i;

	i = 0;
	while (env)
	{
		res = ft_strnstr(env->content, var, ft_strlen(var));
		if (res != NULL)
		{
			if (res[ft_strlen(var)] == '=' || res[ft_strlen(var)] == '\0')
				return (i);
		}
		env = env->next;
		i++;
	}
	return (-1);
}


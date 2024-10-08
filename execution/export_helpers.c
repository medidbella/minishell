/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:46:48 by midbella          #+#    #+#             */
/*   Updated: 2024/08/25 10:40:34 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	extra_case(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	if (str[i] == '+' && str[i + 1] != '=')
		return (1);
	return (0);
}

int	is_specail_var(t_list **head)
{
	if ((*head)->content[0] == '_' && (*head)->content[1] == '=')
	{
		(*head) = (*head)->next;
		return (1);
	}
	return (0);
}

void	printer(t_list *head, int write_fd, int index, int flag)
{
	while (head)
	{
		flag = 0;
		index = 0;
		if (is_specail_var(&head))
			continue ;
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
	int		i;
	char	*tmp;

	i = 0;
	while (av[i] && av[i] != '+')
		i++;
	if ((!ft_isalpha(av[0]) && av[0] != '_') || extra_case(av))
	{
		tmp = ft_strjoin("minishell: export:`", av);
		print_error(ft_strjoin(tmp, "': not a valid identifier"));
		av[0] = 0;
		*return_val = 1;
		return (free(tmp));
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

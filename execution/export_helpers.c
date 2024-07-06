/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:46:48 by midbella          #+#    #+#             */
/*   Updated: 2024/07/06 14:40:49 by midbella         ###   ########.fr       */
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

void	error_detector(char *av)
{
	char	*tmp;

	if (!ft_isalpha(av[0]) && av[0] != '"')
	{
		tmp = ft_strjoin("minishell: export:`", av);
		print_error(ft_strjoin(tmp, "':not a valid indentifier"));
		av[0] = 0;
		return (free(tmp));
	}
	else if (!double_quotes(av))
		av[0] = 0;
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

t_list	*envron_dup(void)
{
	extern char	**environ;
	int			index;
	t_list		*head;
	t_list		*iter;

	index = 1;
	head = ft_lstnew(ft_strdup(environ[0]));
	iter = head;
	while (environ[index])
	{
		iter->next = ft_lstnew(ft_strdup(environ[index]));
		index++;
		iter = iter->next;
	}
	return (head);
}

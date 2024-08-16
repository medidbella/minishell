/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:50:38 by midbella          #+#    #+#             */
/*   Updated: 2024/08/16 18:02:07 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*envron_dup(char **environ)
{
	int			index;
	char		*str;
	t_list		*head;
	t_list		*iter;

	if (!environ[0])
	{
		str = getcwd(NULL, PATH_MAX);
		head = ft_lstnew(ft_strjoin("PWD=", str));
		iter = ft_lstnew(ft_strdup("OLDPWD"));
		ft_lstadd_back(&head, iter);
		return (free(str), head);
	}
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

char	**prep_env(t_list *env)
{
	int		index;
	int		size;
	char	**res;	

	size = ft_lstsize(env);
	res = malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	res[size] = NULL;
	index = 0;
	while (env)
	{
		res[index] = env->content;
		env = env->next;
		index++;
	}
	return (res);
}

char	*ft_get_env(char *var, t_list *env)
{
	int	index;
	int	position;

	position = var_finder(env, var);
	index = -1;
	if (position == -1)
		return (NULL);
	while (++index != position)
		env = env->next;
	index = 0;
	while (env->content[index] != '=' && env->content[index])
		index++;
	return (&env->content[index + 1]);
}

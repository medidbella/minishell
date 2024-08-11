/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:07:40 by midbella          #+#    #+#             */
/*   Updated: 2024/08/11 22:34:11 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexicographical_sort(t_list *head, int write_fd)
{
	int		flag;
	int		iter;
	t_list	*first;
	t_list	*second;

	head = ft_listdup(head);
	first = head;
	flag = 1;
	while (1)
	{
		second = first->next;
		iter = 0;
		if (sort_helper(first->content, second->content))
			swap_str(&first->content, &second->content, &flag);
		first = first->next;
		if (!first->next)
		{
			first = head;
			if (flag == 0)
				break ;
			flag = 0;
		}
	}
	printer(head, write_fd);
	lstfree(head);
}

void	new_environ(t_list *env, char *var, char *val)
{
	int		count;
	char	*new_val;
	int		i;

	i = 0;
	count = 0;
	if (!val)
		return (ft_lstadd_back(&env, ft_lstnew(ft_strdup(var))));
	if (val[0] == '+')
		val++;
	while (val[i])
		if (val[i++] == '"')
			count++;
	i = 0;
	new_val = malloc(sizeof(char) * (ft_strlen(val) - count) + 1);
	new_val[(ft_strlen(val) - count)] = 0;
	while (val[i])
	{
		if (val[i] != '"')
			new_val[i] = val[i];
		i++;
	}
	ft_lstadd_back(&env, ft_lstnew(ft_strjoin(var, new_val)));
	free(new_val);
}

void	modify_environ(t_list *env, char *new_val, int var_index)
{
	char	*tmp;
	int		i;

	if (!new_val)
		return ;
	i = -1;
	while (++i != var_index)
		env = env->next;
	i = 0;
	while (env->content[i] && env->content[i] != '=')
		i++;
	if (new_val[0] != '+')
	{
		tmp = env->content;
		tmp[i] = 0;
		env->content = ft_strjoin(tmp, new_val);
		return (free(tmp));
	}
	new_val += 2;
	if (env->content[i] == 0)
		new_val = ft_strjoin("+", new_val);
	tmp = env->content;
	env->content = ft_strjoin(tmp, new_val);
	free(tmp);
}

void	export_judger(char *arg, t_list *env)
{
	char	*var;
	char	*value;
	int		i;

	if (!arg[0])
		return ;
	i = 0;
	while (arg[i] && arg[i] != '=' && arg[i] != '+')
		i++;
	value = NULL;
	if (arg[i])
		value = ft_substr(arg, i, INT_MAX);
	var = ft_substr(arg, 0, i);
	i = var_finder(env, var);
	if (i == -1)
		new_environ(env, var, value);
	else
		modify_environ(env, value, i);
	return (free(var), free(value));
}

int	ft_export(t_holder *mem, int write_fd)
{
	int	return_val;
	int	i;

	i = 1;
	if (write_fd == -1)
		write_fd = 1;
	return_val = 0;
	if (!mem->input->cmd_av[1] && mem->env)
		return (lexicographical_sort(mem->env, write_fd), 0);
	while (mem->input->cmd_av[i])
	{
		error_detector(mem->input->cmd_av[i], &return_val);
		export_judger(mem->input->cmd_av[i], mem->env);
		i++;
	}
	return (return_val);
}

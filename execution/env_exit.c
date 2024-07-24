/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:38:45 by midbella          #+#    #+#             */
/*   Updated: 2024/07/24 12:32:57 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	locate_char(char *str, char c)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == c)
			return (1);
		index++;
	}
	return (0);
}

int	env_helper(t_list *env, int write_fd)
{
	int	i;

	if (write_fd == -1)
		write_fd = 1;
	while (env)
	{
		if (locate_char(env->content, '='))
		{
			i = 0;
			while (env->content[i])
				ft_putchar_fd(env->content[i++], write_fd);
			ft_putchar_fd('\n', write_fd);
		}
		env = env->next;
	}
	return (0);
}

int	ft_env(t_holder *mem, int write_fd)
{
	int	id;
	int	r_val;

	if (!mem->pipes)
		return (env_helper(mem->env, write_fd), 0);
	id = fork();
	if (id == -1)
		return (1);
	if (id == 0)
	{
		if (write_fd == -1)
		write_fd = 1;
		close_unused_pipes(mem->pipes, write_fd, -1);
		r_val = env_helper(mem->env, write_fd);
		close(write_fd);
		exit(r_val);
	}
	wait(&r_val);
	close(write_fd);
	return (r_val);
}

void	exit_helper(char **av, int *flag)
{
	int	i;

	i = 0;
	while (av[1] && av[1][i])
	{
		if (!ft_isdigit(av[1][i++]))
		{
			ft_putstr_fd("exit\nminishell: exit: numeric argument required\n", 2);
			if (*flag)
				exit(2);
		}
	}
	if (av[1] && av[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		*flag = 0;
		return ;
	}
	return ;
}

int	ft_exit(t_holder *mem)
{
	int	i;
	int	exit_val;
	int	flag;

	exit_val = 0;
	i = 0;
	flag = 0;
	if (!mem->pipes)
		flag = 1;
	exit_helper(mem->input->cmd_av, &flag);
	if (!flag)
		return (1);
	if (mem->input->cmd_av[1])
		exit_val = ft_atoi(mem->input->cmd_av[1]);
	if (flag)
	{
		ft_putstr_fd("exit\n", 1);
		free_inputs(mem->input);
		lst_free(mem->env);
		exit(exit_val);
	}
	return (exit_val);
}

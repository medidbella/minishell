/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:38:45 by midbella          #+#    #+#             */
/*   Updated: 2024/08/25 11:08:38 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_helper(t_input *input, t_list *env, int write_fd)
{
	int	i;

	if (write_fd == -1)
		write_fd = 1;
	if (input->cmd_av[1])
		return (ft_putstr_fd("minishell: env takes no arguments\n", 2), 1);
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
		return (g_status->r_val = env_helper(mem->input, mem->env,
				write_fd), 0);
	id = fork();
	if (id == -1)
		return (1);
	if (!mem->input->next)
		g_status->last_cmd_pid = id;
	if (id == 0)
	{
		if (write_fd == -1)
			write_fd = 1;
		r_val = env_helper(mem->input, mem->env, write_fd);
		child_mem_free(mem, NULL);
		ft_close(write_fd);
		exit(r_val);
	}
	ft_close(write_fd);
	return (0);
}

int	exit_helper(char **av, int *flag, int *r_val, t_holder *mem)
{
	if (av[1] && !is_numeric(av[1]))
	{
		ft_putstr_fd("exit\nminishell: exit: numeric argument required\n", 2);
		if (*flag)
			return (free_inputs(mem->input), lstfree(mem->env),
				free(g_status->cur_pwd), exit(2), 0);
		else
			return (*r_val = 2, 0);
	}
	if (av[1] && av[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		return (*r_val = 1, *flag = -1, 0);
	}
	if (av[1])
		return (*r_val = ft_atoi(av[1]));
	return (*r_val = g_status->r_val);
}

int	ft_exit(t_holder *mem)
{
	int	exit_val;
	int	flag;

	exit_val = 0;
	flag = 0;
	if (!mem->pipes)
		flag = 1;
	exit_helper(mem->input->cmd_av, &flag, &exit_val, mem);
	if (flag <= 0)
		return (g_status->r_val = exit_val, 0);
	if (flag != -1)
	{
		ft_putstr_fd("exit\n", 2);
		free_inputs(mem->input);
		lstfree(mem->env);
		free(g_status->cur_pwd);
		rl_clear_history();
		exit(exit_val);
	}
	return (g_status->r_val = exit_val, 0);
}

int	is_big(char *str)
{
	int	i;
	int	result;
	int	sign;

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
		if (result >= 999)
			return (1);
		i++;
	}
	return (0);
}

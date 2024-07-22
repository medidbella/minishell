/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:38:45 by midbella          #+#    #+#             */
/*   Updated: 2024/07/22 10:47:35 by alaktari         ###   ########.fr       */
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
	int	i;

	if (write_fd == -1)
		write_fd = 1;
	if (!mem->pipes)
		return (env_helper(mem->env, write_fd), 0);
	id = fork();
	if (id == -1)
		return (1);
	if (id == 0)
	{
		close_unused_pipes(mem->pipes, write_fd, -1);
		r_val = env_helper(mem->env, write_fd);
		close(write_fd);
		exit(r_val);
	}
	wait(&r_val);
	close(write_fd);
	return (r_val);
}

void	ft_exit(t_holder *mem)
{
	if (!mem->pipes)
	{
		free_inputs(mem->input);
		lst_free(mem->env);
		exit(0);
	}
	return ;
}

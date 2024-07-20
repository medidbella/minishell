/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:38:45 by midbella          #+#    #+#             */
/*   Updated: 2024/07/19 17:57:59 by midbella         ###   ########.fr       */
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

void	env_helper(t_list *env, int write_fd)
{
	int i;

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
}

int	ft_env(t_holder *mem, int write_fd)
{
	int	id;
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
		env_helper(mem->env, write_fd);
		close(write_fd);
		exit(0);
	}
	wait(NULL);
	close(write_fd);
	return (0);
}

void	ft_exit(t_holder *mem)
{
	if (!mem->pipes)
	{
		free_t_inputs(mem->input);
		lst_free(mem->env);
		exit(0);
	}
	return ;
}

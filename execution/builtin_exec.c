/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:01:24 by midbella          #+#    #+#             */
/*   Updated: 2024/07/19 18:01:16 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exec_builtin_helper(t_holder *mem, int write_fd)
{
	int	r_val;
	int	id;

	if (!mem->pipes)
		return (ft_export(mem, write_fd));
	id = fork();
	if (id == -1)
		return (1);
	if (id == 0)
	{
		close_unused_pipes(mem->pipes, write_fd, -1);
		r_val = ft_export(mem, write_fd);
		close(write_fd);
		exit(r_val);
	}
	wait(&r_val);
	close(write_fd);
	return (r_val);
}

int	exec_builtin(t_holder *mem, int write_fd, int read_fd)
{
	if (!ft_strncmp("env", mem->input->cmd_av[0], 6))
		return (ft_env(mem, write_fd));
	else if (!ft_strncmp("cd", mem->input->cmd_av[0], 6))
		return (ft_cd(mem));
	else if (!ft_strncmp("pwd", mem->input->cmd_av[0], 6))
		return (ft_pwd(mem, write_fd));
	else if (!ft_strncmp("echo", mem->input->cmd_av[0], 6))
		return (ft_echo(mem, write_fd));
	else if (!ft_strncmp("unset", mem->input->cmd_av[0], 6))
		return (ft_unset(mem->input, &mem->env));
	else if (!ft_strncmp("exit", mem->input->cmd_av[0], 6))
		ft_exit(mem);
	if (!ft_strncmp("export", mem->input->cmd_av[0], 6))
		return (exec_builtin_helper(mem, write_fd));
	return (0);
}

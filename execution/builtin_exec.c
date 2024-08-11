/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:01:24 by midbella          #+#    #+#             */
/*   Updated: 2024/08/09 17:54:08 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pre_cd(t_holder *mem)
{
	char	*new_dir;
	char	*curr_dir;

	if (!mem->input->cmd_av[1])
	{
		new_dir = ft_get_env("HOME", mem->env);
		if (!new_dir)
			return (ft_putstr_fd("cd: HOME not set", 2), 1);
		free(mem->input->cmd_av);
		mem->input->cmd_av = ft_split(ft_strjoin("cd ", new_dir), ' ');
	}
	else if (!ft_strncmp(mem->input->cmd_av[1], "-", 2))
	{
		new_dir = ft_get_env("OLDPWD", mem->env);
		if (!new_dir)
			return (ft_putstr_fd("cd: OLDPWD not set\n", 2), 1);
		free(mem->input->cmd_av[1]);
		mem->input->cmd_av[1] = ft_strdup(new_dir);
	}
	curr_dir = getcwd(NULL, PATH_MAX);
	return (ft_cd(mem, curr_dir));
}

int	exec_builtin_helper(t_holder *mem, int write_fd)
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
	return (WEXITSTATUS(r_val));
}

int	exec_builtin(t_holder *mem, int write_fd, int read_fd)
{
	if (!mem->input->cmd_av)
		return (0);
	close(read_fd);
	if (!ft_strncmp("env", mem->input->cmd_av[0], 6))
		return (ft_env(mem, write_fd));
	else if (!ft_strncmp("cd", mem->input->cmd_av[0], 6))
		return (pre_cd(mem));
	else if (!ft_strncmp("pwd", mem->input->cmd_av[0], 6))
		return (ft_pwd(mem, write_fd));
	else if (!ft_strncmp("echo", mem->input->cmd_av[0], 6))
		return (ft_echo(mem, write_fd));
	else if (!ft_strncmp("unset", mem->input->cmd_av[0], 6))
	{
		if (!mem->pipes)
			return (ft_unset(mem->input, &mem->env));
		else
			return (0);
	}
	else if (!ft_strncmp("exit", mem->input->cmd_av[0], 6))
		return (ft_exit(mem));
	if (!ft_strncmp("export", mem->input->cmd_av[0], 6))
		return (exec_builtin_helper(mem, write_fd));
	return (0);
}

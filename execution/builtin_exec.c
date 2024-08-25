/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:01:24 by midbella          #+#    #+#             */
/*   Updated: 2024/08/24 22:12:27 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pre_unset(t_holder *mem, int write_fd)
{
	char	*err_msg;

	if (!mem->pipes)
	{
		g_status->r_val = ft_unset(mem->input, &mem->env);
		return (0);
	}
	err_msg = ("minishell: unset: no option is supported");
	if (mem->input->cmd_av[1] && mem->input->cmd_av[1][0] == '-'
			&& mem->input->cmd_av[1][1])
	{
		if (!mem->input->next)
			g_status->r_val = 2;
		return (print_error(ft_strdup(err_msg)), 2);
	}
	if (!mem->input->next)
		g_status->r_val = 0;
	ft_close(write_fd);
	return (0);
}

void	cd_child_case(t_holder *mem, char *path)
{
	int	r_val;

	r_val = 0;
	if (mem->input->cmd_av[2])
	{
		print_error(ft_strdup("cd: too many arguments"));
		r_val = 1;
	}
	if (chdir(mem->input->cmd_av[1]) != 0)
	{
		perror(NULL);
		r_val = 1;
	}
	free(path);
	child_mem_free(mem, NULL);
	exit(r_val);
}

int	pre_cd(t_holder *mem, int write_fd)
{
	char	*new_dir;
	char	*tmp;
	char	*curr_dir;

	curr_dir = getcwd(NULL, PATH_MAX);
	if (!mem->input->cmd_av[1])
	{
		new_dir = ft_get_env("HOME", mem->env);
		if (!new_dir || !new_dir[0])
		{
			g_status->r_val = 1;
			return (free(curr_dir), ft_putstr_fd("cd: HOME not set\n", 2), 1);
		}
		free_strings(mem->input->cmd_av);
		return (tmp = ft_strjoin("cd ", new_dir), mem->input->cmd_av = ft_split
			(tmp, ' '), free(tmp), ft_close(write_fd), ft_cd(mem, curr_dir));
	}
	return (ft_close(write_fd), ft_cd(mem, curr_dir));
}

int	exec_builtin_helper(t_holder *mem, int write_fd)
{
	int	r_val;
	int	id;

	if (!mem->pipes)
		return (g_status->r_val = ft_export(mem, write_fd), 0);
	id = fork();
	if (id == -1)
		return (1);
	if (!mem->input->next)
		g_status->last_cmd_pid = id;
	if (id == 0)
	{
		r_val = ft_export(mem, write_fd);
		child_mem_free(mem, NULL);
		ft_close(write_fd);
		exit(r_val);
	}
	ft_close(write_fd);
	return (0);
}

int	exec_builtin(t_holder *mem, int write_fd, int read_fd)
{
	if (!mem->input->cmd_av)
		return (0);
	if (set_file_descriptors(mem, &write_fd, &read_fd))
	{
		if (!mem->input->next)
			return (g_status->last_cmd_pid = 0, g_status->r_val = 1, 1);
		return (1);
	}
	ft_close(read_fd);
	if (!ft_strncmp("env", mem->input->cmd_av[0], 6))
		return (ft_env(mem, write_fd));
	else if (!ft_strncmp("cd", mem->input->cmd_av[0], 6))
		return (pre_cd(mem, write_fd));
	else if (!ft_strncmp("pwd", mem->input->cmd_av[0], 6))
		return (ft_pwd(mem, write_fd));
	else if (!ft_strncmp("echo", mem->input->cmd_av[0], 6))
		return (ft_echo(mem, write_fd));
	else if (!ft_strncmp("unset", mem->input->cmd_av[0], 6))
		return (pre_unset(mem, write_fd));
	else if (!ft_strncmp("exit", mem->input->cmd_av[0], 6))
		return (ft_exit(mem));
	if (!ft_strncmp("export", mem->input->cmd_av[0], 6))
		return (exec_builtin_helper(mem, write_fd));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:01:24 by midbella          #+#    #+#             */
/*   Updated: 2024/07/22 09:49:04 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pre_cd(t_holder *mem)
{
	char	*new_dir;
	char	*tmp;

	if (!mem->input->cmd_av[1])
	{
		new_dir = ft_get_env("HOME", mem->env);
		if (!new_dir)
			return(ft_putstr_fd("cd: HOME not set", 2), 1);
		free(mem->input->cmd_av);
		printf("%s\n", tmp);
		mem->input->cmd_av = ft_split(tmp, ' ');
		free(tmp);
	}
	else if (!ft_strncmp(mem->input->cmd_av[1], "-", 2))
	{
		new_dir = ft_get_env("OLDPWD", mem->env);
		if (!new_dir)
			return(ft_putstr_fd("cd: OLDPWD not set\n", 2), 1);
		free(mem->input->cmd_av[1]);
		mem->input->cmd_av[1] = ft_strdup(new_dir);
	}
	return (ft_cd(mem));
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
	return (r_val);
}

int	exec_builtin(t_holder *mem, int write_fd, int read_fd)
{
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
		return (ft_unset(mem->input, &mem->env));
	else if (!ft_strncmp("exit", mem->input->cmd_av[0], 6))
		ft_exit(mem);
	if (!ft_strncmp("export", mem->input->cmd_av[0], 6))
		return (exec_builtin_helper(mem, write_fd));
	return (0);
}

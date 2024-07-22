/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cd_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:07:05 by midbella          #+#    #+#             */
/*   Updated: 2024/07/21 15:10:44 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_helper(char **av, int write_fd)
{
	int	flag;
	int	index;

	index = 1;
	flag = 0;
	while (av[index])
	{
		if (is_optoin(av[index]) && flag == 0)
		{
			flag = 1;
			while (is_optoin(av[index]) && av[index])
				index++;
		}
		if (!av[index])
			break ;
		ft_putstr_fd(av[index], write_fd);
		if (av[index + 1])
			ft_putchar_fd(' ', write_fd);
		index++;
	}
	if (!flag)
		ft_putchar_fd('\n', write_fd);
}

int	ft_echo(t_holder *mem, int write_fd)
{
	int	id;

	if (write_fd == -1)
		write_fd = 1;
	if (mem->pipes == NULL)
		return (echo_helper(mem->input->cmd_av, write_fd), 0);
	id = fork();
	if (id == -1)
		return (1);
	if (id == 0)
	{
		close_unused_pipes(mem->pipes, write_fd, -1);
		echo_helper(mem->input->cmd_av, write_fd);
		close(write_fd);
		exit(0);
	}
	wait(NULL);
	close(write_fd);
	return (0);
}

void	pwd_helper(int write_fd)
{
	char	*path;

	path = getcwd(NULL, PATH_MAX);
	ft_putstr_fd(path, write_fd);
	ft_putchar_fd('\n', write_fd);
	free(path);
}

int	ft_pwd(t_holder *mem, int write_fd)
{
	char	*path;
	int		id;

	if (write_fd == -1)
		write_fd = 1;
	if (!mem->pipes)
		return (pwd_helper(write_fd), 0);
	id = fork();
	if (id == -1)
		return (1);
	if (id == 0)
	{
		close_unused_pipes(mem->pipes, write_fd, -1);
		pwd_helper(write_fd);
		close(write_fd);
		exit(0);
	}
	wait(NULL);
	close(write_fd);
	return (0);
}

int	ft_cd(t_holder *mem)
{
	int	r_val;
	int	id;

	if (mem->pipes)
	{
		id = fork();
		if (id == 0)
		{
			if (mem->input->cmd_av[2])
				return (print_error(ft_strdup("cd: too many arguments")), 1);
			if (chdir(mem->input->cmd_av[1]) != 0)
				return (perror(NULL), 1);
			exit(0);
		}
		wait(&r_val);
		return (r_val);
	}
	if (mem->input->cmd_av[2])
		return (print_error(ft_strdup("cd: too many arguments")), 1);
	if (chdir(mem->input->cmd_av[1]) != 0)
		return (ft_putstr_fd("cd: ", 2),
			ft_putstr_fd(mem->input->cmd_av[1], 2), perror(NULL), 1);
	return (0);
}
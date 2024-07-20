/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:54:14 by midbella          #+#    #+#             */
/*   Updated: 2024/07/20 12:40:14 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_and_send(char *new_line, char *delimiter, int *flag, int pipe_fd)
{
	int		i;
	char	*res;

	i = 0;
	if (ft_strncmp(new_line, delimiter,
			ft_strlen(new_line) + ft_strlen(delimiter)) != 0)
	{
		if (*flag != 37)
		{
			write(pipe_fd, new_line, ft_strlen(new_line));
			write(pipe_fd, "\n", 1);
		}
		return ;
	}
	*flag = 0;
}

void	here_doc_sim(char *delimiter)
{
	int	flag;

	flag = 37;
	while (flag)
		check_and_send(readline(">"), delimiter, &flag, 0);
}

int	temp_file_create(void)
{
	int	fd;

	fd = open("/tmp/latest_minishell_here_doc", O_CREAT, O_RDWR, 0644);
	if (fd == -1)
		return (perror(NULL), 1);
	return (fd);
}

int	here_doc(t_holder *mem, char *delimiter, int write_fd)
{
	int		fd;
	int		id;
	int		return_val;
	char	*bin_path;

	id = 1;
	if (temp_file_create == -1)
		return (1);
	while (id)
		check_and_send(readline(">"), delimiter, &id, fd);
	bin_path = find_path(mem->input->cmd_av[0]);
	id = fork();
	if (id == 0)
	{
		close_unused_pipes(mem->pipes, write_fd, -1);
		if (write_fd >= 0)
			dup2(write_fd, 1);
		close(write_fd);
		dup2(fds[0], 0);
		close(fds[0]);
		execve(bin_path, mem->input->cmd_av, NULL);
		return (print_error(ft_strjoin("command not found :", bin_path)), 127);
	}
	wait(&return_val);
	return (close(fds[0]), return_val);
}

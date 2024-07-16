/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:54:14 by midbella          #+#    #+#             */
/*   Updated: 2024/07/15 17:55:05 by midbella         ###   ########.fr       */
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

int	here_doc(char **cmd_av, char *delimiter, int write_fd)
{
	int		fds[2];
	int		id;
	int		return_val;
	char	*bin_path;

	id = 1;
	if (pipe(fds) != 0)
		return (-3);
	while (id)
		check_and_send(readline(">"), delimiter, &id, fds[1]);
	close(fds[1]);
	bin_path = find_path(cmd_av[0]);
	id = fork();
	if (id == 0)
	{
		close(fds[1]);
		if (write_fd >= 0)
			dup2(write_fd, 1);
		dup2(fds[0], 0);
		close(fds[0]);
		close(write_fd);
		execve(bin_path, cmd_av, NULL);
	}
	wait(&return_val);
	return (close(fds[0]), return_val);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:54:14 by midbella          #+#    #+#             */
/*   Updated: 2024/07/29 20:21:45 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_log_file()
{
	char	*av[4];
	int		id;

	id = fork();
	if (id == 0)
	{
		av[0] = "rm";
		av[1] = "-f";
		av[2] = "/tmp/latest_minishell_here_doc";
		av[3] = NULL;
		execve("/usr/bin/rm", av, NULL);
		exit(0);
	}
	wait(&id);
	return ;
}

void	check_and_send(char *new_line, char *delimiter, int *flag, int pipe_fd)
{
	if (!new_line)
	{
		print_error(ft_strjoin("warning: here-doc delimited by EOF, wanted ",
			delimiter));
		*flag = 0;
		return ;
	}
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

int	here_doc(t_holder *mem, char *delimiter, int write_fd)
{
	int		fds[2];
	int		flag;

	del_log_file();
	if (!mem->input)
		return (here_doc_sim(delimiter), 0);
	fds[0] = open("/tmp/latest_minishell_here_doc", O_CREAT | O_RDWR, 0644);
	if (fds[0] == -1)
		return (perror(NULL), 1);
	fds[1] = open("/tmp/latest_minishell_here_doc", O_RDWR, 0644);
	if (fds[1] == -1)
		return (perror(NULL), 1);
	flag = 1;
	while (flag)
		check_and_send(readline(">"), delimiter, &flag, fds[1]);
	return (executer(mem, write_fd, fds[0]));
}

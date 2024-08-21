/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:54:14 by midbella          #+#    #+#             */
/*   Updated: 2024/08/21 14:04:11 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_and_send(char *delimiter, int *flag, int pipe_fd, t_list	*env)
{
	char	*new_line;

	new_line = readline(">");
	if (!new_line)
	{
		print_error(ft_strjoin("warning: here-doc delimited by EOF, wanted ",
				delimiter));
		*flag = 0;
		return ;
	}
	if (ft_strncmp(new_line, delimiter, ft_strlen(delimiter) + 1) != 0)
	{
		if (pipe_fd >= 0)
		{
			new_line = get_new_line(new_line, env);
			ft_putstr_fd(new_line, pipe_fd);
			ft_putchar_fd('\n', pipe_fd);
			free(new_line);
		}
		return ;
	}
	*flag = 0;
}

int	here_doc_core(char *delimiter, int *fds, t_holder *mem)
{
	int	flag;
	int	id;

	id = fork();
	if (id == -1)
		return (-1);
	flag = 1;
	signal(SIGINT, SIG_IGN);
	if (id == 0)
	{
		ft_close(fds[0]);
		signal(SIGINT, here_doc_sigint);
		while (flag)
			check_and_send(delimiter, &flag, fds[1], mem->env);
		child_mem_free(mem, NULL);
		ft_close(fds[1]);
		exit(0);
	}
	wait(&flag);
	return (WEXITSTATUS(flag));
}

int	here_doc(t_holder *mem, char *delimiter)
{
	int		fds[2];
	int		flag;

	fds[0] = open("/tmp/latest_here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fds[0] == -1)
		return (perror("/tmp/latest_here_doc"), exit(1), 1);
	fds[1] = open("/tmp/latest_here_doc", O_RDWR);
	if (fds[1] == -1)
		return (perror("/tmp/latest_here_doc"), exit(1), 1);
	flag = here_doc_core(delimiter, fds, mem);
	ft_close(fds[1]);
	if (flag == -1)
		exit (1);
	if (flag)
		return (g_status->stp_flag = 1, exit(130), 1);
	return (fds[0]);
}

int	is_here_doc(t_options *list)
{
	while (list)
	{
		if (list->who == HERE_DOC)
			return (1);
		list = list->next;
	}
	return (0);
}

void	here_doc_wait(int pid)
{
	int	r_val;

	waitpid(pid, &r_val, 0);
	if (WIFSIGNALED(r_val))
		g_status->r_val = 128 + WTERMSIG(r_val);
	else
		g_status->r_val = WEXITSTATUS(r_val);
}

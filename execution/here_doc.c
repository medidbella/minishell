/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:54:14 by midbella          #+#    #+#             */
/*   Updated: 2024/08/24 17:49:25 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_and_send(t_options *list, int *flag, int pipe_fd, t_list	*env)
{
	char	*new_line;

	new_line = readline(">");
	if (!new_line)
	{
		print_error(ft_strjoin("warning: here-doc delimited by EOF, wanted ",
				list->limiter));
		*flag = 0;
		return ;
	}
	if (ft_strncmp(new_line, list->limiter, ft_strlen(list->limiter) + 1) != 0)
	{
		if (list->expand)
			new_line = get_new_line(new_line, env);
		ft_putstr_fd(new_line, pipe_fd);
		ft_putchar_fd('\n', pipe_fd);
		free(new_line);
		return ;
	}
	*flag = 0;
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

int	here_doc_core(t_options *list, int *fds, t_holder *mem)
{
	int	flag;
	int	id;

	id = fork();
	if (id == -1)
		return (-1);
	flag = 1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (id == 0)
	{
		ft_close(fds[0]);
		signal(SIGINT, here_doc_sigint);
		while (flag)
			check_and_send(list, &flag, fds[1], mem->env);
		child_mem_free(mem, NULL);
		free(mem->cmd);
		ft_close(fds[1]);
		exit(0);
	}
	wait(&flag);
	return (WEXITSTATUS(flag));
}

int	here_doc(t_holder *mem, t_options *list, int index)
{
	int		fds[2];
	int		flag;

	if (log_file_create(fds, index) == 1)
		return (-2);
	flag = here_doc_core(list, fds, mem);
	ft_close(fds[1]);
	if (flag == -1)
		return (g_status->r_val = 1, -2);
	if (flag == 1)
		return (g_status->r_val = 130, -2);
	return (fds[0]);
}

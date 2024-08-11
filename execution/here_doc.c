/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:54:14 by midbella          #+#    #+#             */
/*   Updated: 2024/08/10 17:53:04 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_sig	*g_status;

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
	if (ft_strncmp(new_line, delimiter,
			ft_strlen(new_line) + ft_strlen(delimiter)) != 0)
	{
		new_line = ft_expansion(new_line, env, 0, NULL);
		ft_putstr_fd(new_line, pipe_fd);
		ft_putchar_fd('\n', pipe_fd);
		free(new_line);
		return ;
	}
	*flag = 0;
}

int	here_doc_core(char *delimiter, int *fds, int **pipes, t_list *env)
{
	int	flag;
	int	id;

	id = fork();
	if (id == -1)
		return (-1);
	flag = 1;
	if (id == 0)
	{
		close(fds[0]);
		close_unused_pipes(pipes, -1, -1);
		signal(SIGINT, here_doc_sigint);
		while (flag)
			check_and_send(delimiter, &flag, fds[1], env);
		close(fds[1]);
		exit(0);
	}
	wait(&flag);
	return (WEXITSTATUS(flag));
}

void	del_log_file(char *file)
{
	char	*av[4];
	int		id;

	id = fork();
	if (id == 0)
	{
		av[0] = "rm";
		av[1] = "-f";
		av[2] = file;
		av[3] = NULL;
		execve("/usr/bin/rm", av, NULL);
		exit(0);
	}
	wait(&id);
	return ;
}

int	here_doc_sim(char *delimiter, int **pipes)
{
	int	fds[2];
	int	r_val;

	if (g_status->sig_kill_flag == 1)
		return (130);
	fds[1] = -22;
	r_val = here_doc_core(delimiter, fds, pipes, NULL);
	if (r_val == -1)
		return (1);
	else if (r_val)
		return (g_status->sig_kill_flag = 1, 130);
	return (0);
}

int	here_doc(t_holder *mem, char *delimiter, int write_fd)
{
	int		fds[2];
	int		flag;

	if (g_status->sig_kill_flag == 1)
		return (130);
	del_log_file("/tmp/latest_minishell_here_doc");
	if (!mem->input)
		return (here_doc_sim(delimiter, mem->pipes));
	fds[0] = open("/tmp/latest_minishell_here_doc", O_CREAT | O_RDWR, 0644);
	if (fds[0] == -1)
		return (ft_putstr_fd("error: can't open /tmp/latest_minishell_here_doc",
				2), 1);
	fds[1] = open("/tmp/latest_minishell_here_doc", O_RDWR, 0644);
	if (fds[1] == -1)
		return (ft_putstr_fd("error: can't open /tmp/latest_minishell_here_doc",
				2), 1);
	flag = here_doc_core(delimiter, fds, mem->pipes, mem->env);
	close(fds[1]);
	if (flag == -1)
		return (1);
	if (flag)
		return (g_status->sig_kill_flag = 1, 130);
	return (executer(mem, write_fd, fds[0]));
}

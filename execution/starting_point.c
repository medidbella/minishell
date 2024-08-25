/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:39:45 by midbella          #+#    #+#             */
/*   Updated: 2024/08/25 09:29:48 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_input_output(t_options *iter, int *node_idx)
{
	char	*file;
	char	*err;
	int		index;

	index = -1;
	if (*node_idx == -1)
		return (0);
	while (++index != *node_idx)
		iter = iter->next;
	if (iter->who == INPUT_RD)
		file = iter->input;
	if (iter->who == RD_APND || iter->who == RD_TRNC)
		file = iter->out;
	if (iter->who == RD_APND)
		*node_idx = open(iter->out, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (iter->who == RD_TRNC)
		*node_idx = open(iter->out, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (iter->who == INPUT_RD)
		*node_idx = open(iter->input, O_RDONLY);
	err = strerror(errno);
	if (*node_idx < 0)
		return (open_failer(err, file), 1);
	return (0);
}

int	set_file_descriptors(t_holder *mem, int *pipe_wfd, int *pipe_rfd)
{
	int	idx;
	int	write_idx;
	int	read_idx;

	init_vars(&idx, &write_idx, &read_idx);
	if (!mem->input->list)
		return (0);
	set_read_write(mem->input->list, &write_idx, &read_idx);
	if (opt_iter(mem, &write_idx, &read_idx) == 1)
		return (1);
	if (ft_sorter(mem, &write_idx, &read_idx))
		return (1);
	pipe_or_option(&write_idx, &read_idx, pipe_wfd, pipe_rfd);
	if (mem->input->here_doc_fd != -1)
		*pipe_rfd = mem->input->here_doc_fd;
	return (0);
}

void	executer(t_holder *mem, int w_fd, int r_fd)
{
	char	*bin_path;
	int		id;

	bin_path = NULL;
	if (mem->input->type == BUILTIN)
		return (exec_builtin(mem, w_fd, r_fd), free(NULL));
	if (mem->input->cmd_av)
		bin_path = find_path(mem->input->cmd_av[0], mem->env);
	ignore_signals(bin_path);
	id = fork();
	if (id == -1)
		return (free(bin_path));
	if (!mem->input->next)
		g_status->last_cmd_pid = id;
	if (id == 0)
	{
		prep_exeve(mem, w_fd, r_fd, bin_path);
		execve_failure(bin_path, &id);
		exit(id);
	}
	return (ft_close(w_fd), ft_close(r_fd), free(bin_path));
}

void	exec_loop(t_holder *mem, int count)
{
	int	index;

	index = 1;
	if (set_here_doc_fds(mem))
		return ;
	if (count == 1)
		return (mem->pipes = NULL, executer(mem, -1, -1));
	mem->pipes = pipes_creator(count);
	if (!mem->pipes)
	{
		ft_putstr_fd("minishell: can't open pipes\n", 2);
		return (g_status->r_val = 1, free(NULL));
	}
	executer(mem, mem->pipes[0][1], -1);
	mem->input = mem->input->next;
	while (mem->input->next)
	{
		executer(mem, mem->pipes[index][1], mem->pipes[index - 1][0]);
		mem->input = mem->input->next;
		index++;
	}
	executer(mem, -1, mem->pipes[count - 2][0]);
}

int	global_exec(t_holder *mem)
{
	int	r_val;
	int	count;

	r_val = 0;
	count = inputs_count(mem->input);
	if (count == 0)
		return (0);
	exec_loop(mem, count);
	while (1)
	{
		if (waitpid(g_status->last_cmd_pid, &r_val, 0) != -1
			&& g_status->last_cmd_pid != 0)
		{
			if (WIFSIGNALED(r_val))
				g_status->r_val = 128 + WTERMSIG(r_val);
			else
				g_status->r_val = WEXITSTATUS(r_val);
		}
		if (wait(NULL) == -1)
			break ;
	}
	g_status->last_cmd_pid = 0;
	return (close_and_free_pipes(mem->pipes), 0);
}

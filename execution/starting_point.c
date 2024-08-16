/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:39:45 by midbella          #+#    #+#             */
/*   Updated: 2024/08/16 18:47:54 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_sig	*g_status;

int	get_input_output(t_options *iter, int *node_idx, int *her_doc)
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
	else if (iter->who == HERE_DOC)
		return (*her_doc = index, 0);
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
	int	her_doc_flag;

	init_vars(&idx, &write_idx, &read_idx, &her_doc_flag);
	if (!mem->input->list)
		return (0);
	set_read_write(mem->input->list, &write_idx, &read_idx);
	if (opt_iter(mem->input->list, &write_idx, &read_idx) == 1)
		return (1);
	if (ft_sorter(mem->input->list, &write_idx, &read_idx, &her_doc_flag))
		return (1);
	pipe_or_option(&write_idx, &read_idx, pipe_wfd, pipe_rfd);
	if (her_doc_flag != -1)
	{
		while (++idx != her_doc_flag)
			mem->input->list = mem->input->list->next;
		*pipe_rfd = here_doc(mem, mem->input->list->limiter);
	}
	return (0);
}

int	executer(t_holder *mem, int w_fd, int r_fd)
{
	char	*bin_path;
	char	**child_env;
	int		return_val;
	int		id;

	if (!mem->input->cmd_av || mem->input->type == BUILTIN)
		return (exec_builtin(mem, w_fd, r_fd));
	bin_path = find_path(mem->input->cmd_av[0], mem->env);
	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == -1)
		return (free(bin_path), 1);
	if (!mem->input->next)
		g_status->last_cmd_pid = id;
	if (id == 0)
	{
		pre_execve(mem, w_fd, r_fd, &child_env);
		execve(bin_path, mem->input->cmd_av, child_env);
		execve_failure(bin_path, &return_val);
		child_mem_free(mem, child_env);
		exit(return_val);
	}
	if (is_here_doc(mem->input->list))
		waitpid(id, NULL, 0);
	return (close(w_fd), close(r_fd), free(bin_path), g_status->sig_kill_flag);
}

void	exec_loop(t_holder *mem, int count)
{
	int	pipe_index;

	pipe_index = 1;
	if (count == 1)
	{
		mem->pipes = NULL;
		executer(mem, -1, -1);
		return ;
	}
	mem->pipes = pipes_creator(count);
	if (!mem->pipes)
	{
		g_status->r_val = 1;
		return ;
	}
	executer(mem, mem->pipes[0][1], -1);
	mem->input = mem->input->next;
	while (mem->input->next)
	{
		executer(mem, mem->pipes[pipe_index][1],
			mem->pipes[pipe_index - 1][0]);
		mem->input = mem->input->next;
		pipe_index++;
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
			g_status->r_val = WEXITSTATUS(r_val);
		if (wait(NULL) == -1)
			break ;
	}
	g_status->last_cmd_pid = 0;
	signal(SIGINT, sigint_handler);
	return (close_and_free_pipes(mem->pipes), 0);
}

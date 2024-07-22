/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:39:45 by midbella          #+#    #+#             */
/*   Updated: 2024/07/21 15:07:55 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	opt_iter(t_options *opt_lst, int *write_idx, int *read_idx)
{
	int	err_flag;
	int	index;

	index = 0;
	err_flag = 0;
	while (opt_lst->next)
	{
		if (opt_lst->who == HERE_DOC && index != *read_idx)
			here_doc_sim(opt_lst->limiter);
		else if (index != *read_idx && index != *write_idx)
			case_of_error(opt_lst, &err_flag);
		if (err_flag)
			return (1);
		index++;
		opt_lst = opt_lst->next;
	}
	return (0);
}

int	get_input_output(t_options *iter, int *node_idx, int *her_doc)
{
	char	*file;
	int		type;
	char	*err;
	int		index;

	index = -1;
	if (*node_idx == -1)
		return (0);
	while (++index != *node_idx)
		iter = iter->next;
	file = iter->input;
	if (iter->who == RD_APND || iter->who == RD_TRNC)
		file = iter->out;
	if (iter->who == HERE_DOC)
		return (*her_doc = index, 0);
	else if (iter->who == RD_APND)
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

int	executer(t_holder *mem, int w_fd, int r_fd)
{
	char	*bin_path;
	int		return_val;
	int		id;

	if (mem->input->type == BUILTIN)
		return (exec_builtin(mem, w_fd, r_fd));
	bin_path = find_path(mem->input->cmd_av[0], mem->env);
	id = fork();
	if (id == -1)
		return (1);
	if (id == 0)
	{
		close_unused_pipes(mem->pipes, w_fd, r_fd);
		if (w_fd >= 0)
			dup2(w_fd, 1);
		if (r_fd >= 0)
			dup2(r_fd, 0);
		execve(bin_path, mem->input->cmd_av, prep_env(mem->env));
		print_error(ft_strjoin("command not found :", bin_path));
		exit (127);
	}
	wait(&return_val);
	return (close(w_fd), close(r_fd), return_val);
}

int	exec_manager(t_holder *mem, int pipe_wfd, int pipe_rfd)
{
	int			idx;
	int			write_idx;
	int			read_idx;
	int			her_doc_flag;

	write_idx = -1;
	read_idx = -1;
	her_doc_flag = -1;
	if (!mem->input->list)
		return (executer(mem, pipe_wfd, pipe_rfd));
	set_read_write(mem->input->list, &write_idx, &read_idx);
	if (opt_iter(mem->input->list, &write_idx, &read_idx))
		return (1);
	if (ft_sorter(mem->input, &write_idx, &read_idx, &her_doc_flag) == 1)
		return (1);
	pipe_or_option(&write_idx, &read_idx, &pipe_wfd, &pipe_rfd);
	if (her_doc_flag != -1)
	{
		idx = -1;
		read_idx *= -1;
		while (++idx != her_doc_flag)
			mem->input->list = mem->input->list->next;
		return (here_doc(mem, mem->input->list->limiter, write_idx));
	}
	return (executer(mem, write_idx, read_idx));
}

int	global_exec(t_holder *mem)
{
	int	pipe_index;
	int	count;

	count = inputs_count(mem->input);
	pipe_index = 1;
	if (count == 0)
		return (0);
	if (count == 1)
		return (mem->pipes = NULL, exec_manager(mem, -1, -1));
	mem->pipes = pipes_creator(count);
	exec_manager(mem, mem->pipes[0][1], -1);
	mem->input = mem->input->next;
	while (mem->input->next)
	{
		exec_manager(mem, mem->pipes[pipe_index][1],
			mem->pipes[pipe_index - 1][0]);
		mem->input = mem->input->next;
		pipe_index++;
	}
	exec_manager(mem, -1, mem->pipes[count - 2][0]);
	close_and_free_pipes(mem->pipes);
	return (0);
}

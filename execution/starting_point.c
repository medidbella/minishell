/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:39:45 by midbella          #+#    #+#             */
/*   Updated: 2024/07/16 19:01:42 by midbella         ###   ########.fr       */
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

int	executer(t_input *cmd, int w_fd, int r_fd, int **pipes)
{
	char	*bin_path;
	int		return_val;
	int		id;

	id = fork();
	if (id == -1)
		return (1);
	bin_path = find_path(cmd->cmd_av[0]);
	if (id == 0)
	{
		close_unused_pipes(pipes, w_fd, r_fd);
		if (w_fd >= 0)
			dup2(w_fd, 1);
		if (r_fd >= 0)
			dup2(r_fd, 0);
		exit(builtins_or_external(cmd, bin_path));
	}
	close (w_fd);
	close (r_fd);
	wait(&return_val);
	return (free(bin_path), return_val);
}

int	exec_manager(t_input *cmd_node, int pipe_wfd, int pipe_rfd, int **pipes)
{
	int			idx;
	int			write_idx;
	int			read_idx;
	int			her_doc_flag;

	write_idx = -1;
	read_idx = -1;
	her_doc_flag = -1;
	if (!cmd_node->list)
		return (executer(cmd_node, pipe_wfd, pipe_rfd, pipes));
	set_read_write(cmd_node->list, &write_idx, &read_idx);
	if (opt_iter(cmd_node->list, &write_idx, &read_idx))
		return (1);
	if (ft_sorter(cmd_node, &write_idx, &read_idx, &her_doc_flag) == 1)
		return (1);
	pipe_or_option(&write_idx, &read_idx, &pipe_wfd, &pipe_rfd);
	if (her_doc_flag != -1)
	{
		idx = -1;
		read_idx *= -1;
		while (++idx != her_doc_flag)
			cmd_node->list = cmd_node->list->next;
		return (here_doc(cmd_node->cmd_av, cmd_node->list->limiter, write_idx));
	}
	return (executer(cmd_node, write_idx, read_idx, pipes));
}

int	global_exec(t_input *cmd_list)
{
	int	pipe_index;
	int	**pipes;
	int	count;

	count = inputs_count(cmd_list);
	pipe_index = 1;
	if (count == 0)
		return (0);
	if (count == 1)
		return (exec_manager(cmd_list, -1, -1, NULL));
	pipes = pipes_creator(count);
	exec_manager(cmd_list, pipes[0][1], -1, pipes);
	cmd_list = cmd_list->next;
	while (cmd_list->next)
	{
		exec_manager(cmd_list, pipes[pipe_index][1], pipes[pipe_index - 1][0],
			pipes);
		cmd_list = cmd_list->next;
		pipe_index++;
	}
	exec_manager(cmd_list, -1, pipes[count - 2][0], pipes);
	close_and_free_pipes(pipes);
	return (0);
}

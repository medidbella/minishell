/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:41:39 by midbella          #+#    #+#             */
/*   Updated: 2024/08/25 11:01:31 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	opt_iter(t_holder *mem, int *write_idx, int *read_idx)
{
	int			err_flag;
	int			index;
	t_options	*opt;

	index = 0;
	opt = mem->input->list;
	err_flag = 0;
	while (opt->next)
	{
		if (index != *read_idx && index != *write_idx && opt->who != HERE_DOC)
			check_validity(opt, &err_flag);
		if (err_flag)
			return (1);
		index++;
		opt = opt->next;
	}
	return (0);
}

void	set_read_write(t_options *list, int *last_w, int *last_r)
{
	int	index;

	index = 0;
	while (list)
	{
		if (list->who == RD_APND || list->who == RD_TRNC)
			*last_w = index;
		else
			*last_r = index;
		list = list->next;
		index++;
	}
	return ;
}

int	ft_sorter(t_holder *mem, int *write_idx, int *read_idx)
{
	t_options	*opt_list;
	int			idx;

	idx = -1;
	opt_list = mem->input->list;
	if (*write_idx < *read_idx)
	{
		if (get_input_output(opt_list, write_idx) == 1)
			return (1);
		return (get_input_output(opt_list, read_idx) == 1);
	}
	if (get_input_output(opt_list, read_idx) == 1)
		return (1);
	return (get_input_output(opt_list, write_idx));
}

char	*find_path(char *find_me, t_list *env)
{
	char	**paths;
	char	*res;
	char	*holder;
	int		i;

	i = 0;
	holder = find_me;
	find_me = ft_strjoin("/", find_me);
	paths = ft_split(ft_get_env("PATH", env), ':');
	if (!paths || !holder[0] || locate_char(holder, '/'))
		return (free(find_me), free_strings(paths), ft_strdup(holder));
	while (1)
	{
		res = ft_strjoin(paths[i], find_me);
		if (access(res, X_OK) == 0 && !is_dir(res))
			break ;
		free(res);
		i++;
		if (paths[i] == NULL)
			return (free_strings(paths), free(find_me), ft_strdup(holder));
	}
	return (free_strings(paths), free(find_me), res);
}

void	prep_exeve(t_holder *mem, int w_fd, int r_fd, char *bin_path)
{
	char	**child_env;

	mem->cmd = bin_path;
	if (set_file_descriptors(mem, &w_fd, &r_fd) == 1)
		exit(1);
	close_unused_pipes(mem->pipes, w_fd, r_fd);
	if (w_fd >= 0)
	{
		dup2(w_fd, 1);
		ft_close(w_fd);
	}
	if (r_fd >= 0)
	{
		dup2(r_fd, 0);
		ft_close(r_fd);
	}
	child_env = prep_env(mem->env);
	execve(bin_path, mem->input->cmd_av, child_env);
	child_mem_free(mem, child_env);
}

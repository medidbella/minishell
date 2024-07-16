/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:41:39 by midbella          #+#    #+#             */
/*   Updated: 2024/07/16 14:55:12 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	inputs_count(t_input *inpt_list)
{
	int	i;

	i = 0;
	while (inpt_list)
	{
		i++;
		inpt_list = inpt_list->next;
	}
	return (i);
}

void	case_of_error(t_options *tst_node, int *flag)
{
	char	*err;
	char	*file;
	int		fd;

	file = tst_node->out;
	if (tst_node->who == INPUT_RD)
	{
		file = tst_node->input;
		fd = open(tst_node->input, O_RDONLY);
	}
	else
		fd = open(tst_node->out, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
	{
		err = strerror(errno);
		while (tst_node)
		{
			if (tst_node->who == HERE_DOC)
				here_doc_sim(tst_node->limiter);
			tst_node = tst_node->next;
		}
		open_failer(err, file);
		*flag = 1;
	}
	close(fd);
}

void	set_read_write(t_options *list, int *last_w, int *last_r)
{
	int	index;

	index = 0;
	while (list)
	{
		if (list->who == RD_APND || list->who == RD_TRNC)
			*last_w = index;
		else if (list->who == HERE_DOC || list->who == INPUT_RD)
			*last_r = index;
		list = list->next;
		index++;
	}
	return ;
}

int	ft_sorter(t_input *cmd_node, int *write_idx, int *read_idx, int *here_doc)
{
	if (*write_idx < *read_idx)
	{
		if (get_input_output(cmd_node->list, write_idx, here_doc) == 1)
			return (1);
		if (get_input_output(cmd_node->list, read_idx, here_doc) == 1)
			return (1);
	}
	else
	{
		if (get_input_output(cmd_node->list, read_idx, here_doc) == 1)
			return (1);
		if (get_input_output(cmd_node->list, write_idx, here_doc) == 1)
			return (1);
	}
	return (0);
}

char	*find_path(char *find_me)
{
	char	**paths;
	char	*res;
	char	*holder;
	int		i;

	i = 0;
	holder = find_me;
	find_me = ft_strjoin("/", find_me);
	paths = ft_split(getenv("PATH"), ':');
	while (1)
	{
		res = ft_strjoin(paths[i], find_me);
		if (access(res, X_OK) == 0)
			break ;
		free(res);
		i++;
		if (paths[i] == NULL)
			return (free_strings(paths), free(find_me), holder);
	}
	return (free_strings(paths), free(find_me), res);
}

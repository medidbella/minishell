/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:12:22 by midbella          #+#    #+#             */
/*   Updated: 2024/08/24 21:41:53 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	last_here_doc(t_options *list)
{
	while (list)
	{
		if (list->who == HERE_DOC || list->who == INPUT_RD)
			return (0);
		list = list->next;
	}
	return (1);
}

int	iner_here_doc_loop(t_holder *mem, t_options *list, int index)
{
	int	r_val;

	r_val = 0;
	while (list)
	{
		if (list->who == HERE_DOC)
		{
			if (last_here_doc(list->next))
				return (here_doc(mem, list, index));
			else
			{
				r_val = here_doc(mem, list, index);
				if (r_val == -2)
					return (-2);
				else
					ft_close(r_val);
			}
		}
		list = list->next;
	}
	return (-1);
}

int	set_here_doc_fds(t_holder *mem)
{
	int			index;
	int			r_val;
	t_options	*list;
	t_input		*iter;

	index = 0;
	iter = mem->input;
	while (iter)
	{
		list = iter->list;
		r_val = iner_here_doc_loop(mem, list, index);
		if (r_val == -2)
			return (1);
		iter->here_doc_fd = r_val;
		iter = iter->next;
		index++;
	}
	return (0);
}

int	log_file_create(int *fds, int index)
{
	char	*number;
	char	*log_file;

	number = ft_itoa(index);
	log_file = ft_strjoin("/tmp/here_doc_log", number);
	fds[0] = open(log_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	fds[1] = open(log_file, O_RDWR);
	free(number);
	free(log_file);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:05:26 by midbella          #+#    #+#             */
/*   Updated: 2024/07/19 09:38:35 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**pipes_creator(int number)
{
	int	i;
	int	**result;

	i = 0;
	result = malloc(sizeof(int *) * (number));
	result[number - 1] = NULL;
	while (result[i])
	{
		result[i] = malloc(sizeof(int) * 2);
		pipe(result[i]);
		i++;
	}
	return (result);
}

void	close_unused_pipes(int **pipes, int w_fd, int r_fd)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (pipes[i])
	{
		if (pipes[i][0] != r_fd)
			close(pipes[i][0]);
		if (pipes[i][1] != w_fd)
			close(pipes[i][1]);
		i++;
	}
}

void	pipe_or_option(int *write_idx, int *read_idx,
	int *pipe_wfd, int *pipe_rfd)
{
	if (*write_idx == -1)
		*write_idx = *pipe_wfd;
	if (*read_idx == -1)
		*read_idx = *pipe_rfd;
}

void	close_and_free_pipes(int **fds)
{
	int	index;

	index = 0;
	while (fds[index])
	{
		close(fds[index][1]);
		close(fds[index][0]);
		free(fds[index]);
		index++;
	}
	free(fds);
}

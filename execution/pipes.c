/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:05:26 by midbella          #+#    #+#             */
/*   Updated: 2024/08/24 16:20:20 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_prev(int **tab, int index)
{
	while (index >= 0)
	{
		ft_close(tab[index][0]);
		ft_close(tab[index][1]);
		free(tab[index]);
		index--;
	}
	free(tab);
	return ;
}

int	**pipes_creator(int number)
{
	int	i;
	int	**result;

	i = 0;
	result = malloc(sizeof(int *) * (number));
	if (!result)
		return (NULL);
	result[number - 1] = NULL;
	while (i < number - 1)
	{
		result[i] = malloc(sizeof(int) * 2);
		if (!result[i])
			return (free_prev(result, i), NULL);
		if (pipe(result[i]) == -1)
			return (free_prev(result, i), NULL);
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
		if (pipes[i][0] != r_fd && pipes[i][0] != w_fd)
			ft_close(pipes[i][0]);
		if (pipes[i][1] != w_fd && pipes[i][1] != r_fd)
			ft_close(pipes[i][1]);
		i++;
	}
}

void	pipe_or_option(int *write_idx, int *read_idx,
	int *pipe_wfd, int *pipe_rfd)
{
	if (*write_idx != -1)
		*pipe_wfd = *write_idx;
	if (*read_idx != -1)
		*pipe_rfd = *read_idx;
}

void	close_and_free_pipes(int **fds)
{
	int	index;

	index = 0;
	if (!fds)
		return ;
	while (fds[index])
	{
		ft_close(fds[index][1]);
		ft_close(fds[index][0]);
		free(fds[index]);
		index++;
	}
	free(fds);
	fds = NULL;
}

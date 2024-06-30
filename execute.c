/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:54:24 by midbella          #+#    #+#             */
/*   Updated: 2024/06/09 21:54:11 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strings(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	*find_path(char *find_me)
{
	char	**paths;
	char	*res;
	int		i;

	i = 0;
	paths =	ft_split(getenv("PATH"), ':'); 
	res = NULL;
	while (1)
	{
		free(res);
		res = ft_strjoin(paths[i], find_me);
		if (access(res, X_OK) == 0)
			break ;
		i++;
		if (paths[i] == NULL)
			return (free_strings(paths), find_me);
	}
	return (free_strings(paths), res);
}

void close_fds(int **fds, int used_fd, int used_fd2, int size)
{
	static int nb;
	int j;

	j = 0;
	printf(" = = = = = = = = call nb %d\n = = = = = = = = ", nb);
	nb++;
	while (j < size)
	{	
			if (fds[j][1] != used_fd2 && fds[j][1] != used_fd)
			{
				printf("closing =>%d", fds[j][1]);
				close(fds[j][1]);
			}
			if (fds[j][0] != used_fd2 && fds[j][0] != used_fd)
			{
				printf("closing =>%d", fds[j][0]);
				close(fds[j][0]);
			}
		j++;
	}
	printf("the end\n");
}


int	ft_excute(t_input	*tab, int read_fd, int write_fd, int **pipes)
{
	char	*temp;
    int		id;

    tab->cmd = find_path(tab->cmd);
    id = fork();
    if (id == 0)
    {
		if (read_fd != -1 && write_fd == -1)
		{
			close(pipes[0][1]);
			close(pipes[0][0]);
			close(pipes[1][1]);
			dup2(read_fd, 0);
			close(pipes[1][0]);
		}
		else if (write_fd != -1 && read_fd != -1)
		{
			close(pipes[0][1]);
			close(pipes[1][0]);
			dup2(write_fd, 1);
			dup2(read_fd, 0);
			close(pipes[0][0]);
			close(pipes[1][1]);
		}
		else if (write_fd != -1 && read_fd == -1)
		{
			close(pipes[0][0]);
			close(pipes[1][0]);
			close(pipes[1][1]);
			dup2(write_fd, 1);
			close(pipes[0][1]);
		}
		execve(tab->cmd, tab->cmd_av, NULL);
	}
    return (id);
}



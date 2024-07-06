/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:54:24 by midbella          #+#    #+#             */
/*   Updated: 2024/07/06 14:52:48 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**pipes_creator(int number)
{
	int	i;
	int	**result;

	i = 0;
	result = malloc(sizeof(int *) * (number - 1));
	while (i < number - 1)
	{
		result[i] = malloc(sizeof(int) * 2);
		pipe(result[i]);
		i++;
	}
	return (result);
}

int	ft_pipe(t_input	*tab, int size)
{
	int index;
	int	*pids;
	int return_val;
	int **pipes;

	pipes = pipes_creator(size);
	pids = malloc(sizeof(int) * size);
	pids[0] = ft_excute(&tab[0], -1, pipes[0][1], pipes);
	pids[1] = ft_excute(&tab[1], pipes[0][0], pipes[1][1], pipes);
	pids[2] = ft_excute(&tab[2], pipes[1][0], -1, pipes);
	index = 0;
	while (index < size)
	{
		waitpid(pids[index], &return_val, 0);
		index++;
	}
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);
	index = 0;
	while (index >= 0)
		free(pipes[index++]);
	free(pipes);
	free(pids);
	return (return_val);
}

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
	nb++;
	while (j < size)
	{	
			if (fds[j][1] != used_fd2 && fds[j][1] != used_fd)
				close(fds[j][1]);
			if (fds[j][0] != used_fd2 && fds[j][0] != used_fd)
				close(fds[j][0]);
		j++;
	}
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

int main()
{
	t_input *tab;

	tab = malloc(sizeof(t_input) * 3);
	tab[0].cmd = "/cat";
	tab[1].cmd = "/grep";
	tab[2].cmd = "/wc";
	tab[0].cmd_av = ft_split("cat -e -n notes.txt", ' ');
	tab[1].cmd_av = ft_split("grep d", ' ');
	tab[2].cmd_av = ft_split("wc -c", ' ');
	ft_pipe(tab, 3);
	free_strings(tab[0].cmd_av);
	free_strings(tab[1].cmd_av);
	free_strings(tab[2].cmd_av);
}

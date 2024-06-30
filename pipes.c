/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:58:49 by midbella          #+#    #+#             */
/*   Updated: 2024/06/09 21:53:10 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

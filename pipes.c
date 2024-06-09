/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:58:49 by midbella          #+#    #+#             */
/*   Updated: 2024/06/09 19:34:02 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe(t_input	*tab, int size)
{
	int return_val;
	int fds[2];//[0]read [1]write

	pipe(fds);
	ft_excute(tab[0].cmd, tab[0].cmd_av, 0, fds[1]);
	return_val = ft_excute(tab[1].cmd, tab[1].cmd_av, fds[0], 1);
	return (return_val);
}

int main()
{
	t_input tab[2];

	tab[0].cmd = "/bin/cat";
	tab[1].cmd = "/bin/wc";
	tab[0].cmd_av = ft_split("cat notes.txt", ' ');
	tab[1].cmd_av = ft_split("wc -l", ' ');
	int		fds[2];
	
	pipe(fds);
	int id = fork();

	if (id == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		execve(tab[0].cmd, tab[0].cmd_av, NULL);
	}
	int id2 = fork();
	if (id2 == 0)
	{
		close(fds[1]);
		dup2(fds[0], 0);
		execve(tab[1].cmd, tab[1].cmd_av, NULL);
	}
	close(fds[0]);
	close(fds[1]);
	waitpid(id, NULL, 0);
	waitpid(id2, NULL, 0);
	free_strings(tab[0].cmd_av);
	free_strings(tab[1].cmd_av);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:54:14 by midbella          #+#    #+#             */
/*   Updated: 2024/06/08 14:49:36 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(t_input *input, char *to_file, int mode)// >> || >
{
	int fd;
	int id;
	int return_val;

	fd = open(to_file, O_CREAT | O_RDWR | mode, 0666);
	input->cmd = find_path(input->cmd);
	id = fork();
	if (id == 0)
	{
		dup2(fd, 1);
		close(fd);
		execve(input->cmd, input->cmd_av, NULL);
	}
	else 
		wait(&return_val);
	close(fd);
	return (return_val);
}

int redirect_countent(t_input *input, char *in_file) // <
{
	int fd;
	int id;
	int return_val;

	fd = open(in_file, O_CREAT | O_RDONLY, 0666);
	input->cmd = find_path(input->cmd);
	id = fork();
	if (id == 0)
	{
		dup2(fd, 0);
		close(fd);
		execve(input->cmd, input->cmd_av, NULL);
	}
	else 
		wait(&return_val);
	close(fd);
	return (return_val);
}
//you have to emplement "<<" later

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:54:14 by midbella          #+#    #+#             */
/*   Updated: 2024/06/06 21:57:27 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(char *cmd, char **argv, char *to_file, int mode)
{
	int fd;
	int return_val;
	if (mode == 0)
		fd = open(to_file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	else
		fd = open(to_file, O_CREAT | O_RDWR | O_APPEND, 0666);
	return_val = ft_excute(cmd, argv, 0, fd);
	return (return_val);
}

int redirect_countent(char *cmd, char **argv, char *in_file)
{
	int fd;
	int return_val;
	fd = open(in_file, O_RDONLY, 0444);
	return_val = ft_excute(cmd, argv, fd, 1);
}

int main()
{
	
}
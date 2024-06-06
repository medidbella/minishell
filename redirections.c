/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:54:14 by midbella          #+#    #+#             */
/*   Updated: 2024/06/06 19:55:24 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirect(char *cmd, char **argv, char *to_file)
{
	int	pipe_fds[2];
	int fd;
	int return_val;
	
	fd = open(to_file, O_CREAT | O_WRONLY, 0666);
	ft_excute(cmd, argv, 0, fd);
	return (return_val);
}
int main(int ac, char **av)
{
	char *str = av[ac - 1];
	av[ac - 1] = NULL;
	ft_redirect(av[1], av+1, str);
}
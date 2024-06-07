/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:01:08 by midbella          #+#    #+#             */
/*   Updated: 2024/06/06 21:00:30 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include "libft/libft.h"

void	free_strings(char **strs);
char	*find_path(char *find_me);
int		ft_excute(char *cmd, char **args, int r_fd, int w_fd);
int		redirect_input(char *cmd, char **argv, char *to_file, int mode);

#endif
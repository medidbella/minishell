/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:01:08 by midbella          #+#    #+#             */
/*   Updated: 2024/06/30 15:49:47 by midbella         ###   ########.fr       */
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
# include <limits.h>
# include "libft/libft.h"

typedef struct s_input
{
	char	*cmd;
	char	**cmd_av;
} t_input;


void	free_strings(char **strs);
char	*find_path(char *find_me);
void	close_fds(int **fds, int used_fd, int used_fd2, int size);
int		ft_excute(t_input	*tab, int read_fd, int write_fd, int **pipes);
int		redirect_input(t_input *input, char *to_file, int mode);
int		redirect_countent(t_input *input, char *in_file);
void    print_error(char *str);

#endif
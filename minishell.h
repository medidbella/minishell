/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:01:08 by midbella          #+#    #+#             */
/*   Updated: 2024/07/06 15:03:00 by midbella         ###   ########.fr       */
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
	char			**cmd_av;
	struct s_input	*next;
}	t_input;

void	free_strings(char **strs);
char	*find_path(char *find_me);
void	close_fds(int **fds, int used_fd, int used_fd2, int size);
int		ft_excute(t_input	*tab, int read_fd, int write_fd, int **pipes);
int		redirect_input(t_input *input, char *to_file, int mode);
int		redirect_countent(t_input *input, char *in_file);
t_list	*envron_dup(void);
void	swap_str(char **str1, char **str2, int *flag);
void	lst_free(t_list *list);
void	printer(t_list *head);
void	print_error(char *str);
t_list	*ft_listdup(t_list *list);
int		sort_helper(char *str1, char *str2);
int		double_quotes(char *str);
int		var_finder(t_list *env, char *var);
void	error_detector(char *av);

#endif
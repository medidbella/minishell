/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:39:16 by midbella          #+#    #+#             */
/*   Updated: 2024/08/16 18:41:10 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_failer(char *err_msg, char *file)
{
	if (!file || !file[0])
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		return ;
	}
	write(2, err_msg, ft_strlen(err_msg));
	write(2, ": ", 2);
	write(2, file, ft_strlen(file));
	write(2, "\n", 1);
}

void	print_error(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		write(2, &str[i++], 1);
	write(2, "\n", 1);
	free(str);
}

int	is_dir(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

void	cheack_validity(t_options *tst_node, int *flag)
{
	char	*err;
	char	*file;
	int		fd;

	file = tst_node->out;
	if (tst_node->who == INPUT_RD)
	{
		file = tst_node->input;
		fd = open(file, O_RDONLY);
	}
	else
		fd = open(tst_node->out, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
	{
		err = strerror(errno);
		while (tst_node)
		{
			if (tst_node->who == HERE_DOC)
				here_doc_sim(tst_node->limiter);
			tst_node = tst_node->next;
		}
		open_failer(err, file);
		*flag = 1;
	}
	close(fd);
}

int	execve_failure(char *cmd, int *r_val)
{
	char	*err;

	*r_val = 127;
	if (locate_char(cmd, '/') && access(cmd, X_OK) != 0)
	{
		err = strerror(errno);
		if (errno == 13)
			*r_val = 126;
		ft_putstr_fd("minishell: ", 2);
		cmd = ft_strjoin(cmd, " ");
		return (print_error(ft_strjoin(cmd, err)), free(cmd), 0);
	}
	else if (locate_char(cmd, '/') && is_dir(cmd))
		return (ft_putstr_fd("minishell: ", 2),
			print_error(ft_strjoin(cmd, " Is a directory")), *r_val = 126, 0);
	else if (locate_char(cmd, '/'))
		return (ft_putstr_fd("minishell: ", 2),
			print_error(ft_strjoin(cmd, " Is a regular file")), *r_val = 1, 0);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (0);
}

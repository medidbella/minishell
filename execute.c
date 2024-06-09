/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:54:24 by midbella          #+#    #+#             */
/*   Updated: 2024/06/09 21:54:11 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strings(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		//free(strs[i]);
		i++;
	}
	//free(strs);
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
			return (free(find_me), free(res), free_strings(paths), NULL);
	}
    //free(find_me);
	return (free_strings(paths), res);
}

int ft_excute(char *cmd, char **args, int fds[2], char state)
{
	char	*temp;
    int		id;
    int		return_val;

	temp = cmd;
	cmd = ft_strjoin("/", cmd);
    cmd = find_path(cmd);
	if (cmd == NULL)
		cmd = temp;
    id = fork();
    if (id == 0)
    {
		if (state == 'r')
		{
			close(fds[1]);
        	dup2(fds[0], 0);
		}
		else
		{
			close(fds[0]);
        	dup2(fds[1], 1);
		}
        execve(cmd, args, NULL);
    }
    else 
        wait(&return_val);
    //free(cmd);
    return (return_val);
}

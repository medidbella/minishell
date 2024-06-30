/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:07:05 by midbella          #+#    #+#             */
/*   Updated: 2024/06/30 16:21:45 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_optoin(char *arg)
{
    int index;

    index = 0;
    if (ft_strlen(arg) == 2 && arg[0] == '-' && arg[1] == 'n')
        return (1);
    else
        return (0);
}

int ft_echo(t_input *data)
{
    int flag;
    int index;
    
    index = 0;
    flag = 0;
    while (data->cmd_av[index])
    {
        if (is_optoin(data->cmd_av[0]) && flag == 0)
        {
            flag = 1;
            while (is_optoin(data->cmd_av[index]))
                index++;
        }
        printf("%s", data->cmd_av[index]);
        if (data->cmd_av[index + 1])
            printf(" ");
        index++;
    }
    if (!flag)
        printf("\n");
    return(0);
} 

int ft_cd(t_input *data)//the parser should handle the case of an absolute path && '-' && cd only
{
    char *path;
    char buff[PATH_MAX];
    
    if (data->cmd_av[1])
        return (print_error(ft_strdup("cd: too many arguments")), 1);
    if (chdir(data->cmd_av[0]) != 0)
            return (print_error(ft_strjoin("cd: no such file or directory: ", data->cmd_av[0])), 1);
    return (0);
}

int ft_pwd(t_input *data)
{
    if (data->cmd_av)
        return (print_error(ft_strdup("pwd: too many arguments")), 1);
    else 
        printf("%s\n", getenv("PWD"));
    return (0);
}
int main()
{
    t_input mem;
    char *st[] = {"arg", NULL};
    mem.cmd_av = NULL;
    
}
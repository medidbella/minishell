/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:07:40 by midbella          #+#    #+#             */
/*   Updated: 2024/07/02 17:07:47 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int is_sorted(char **tab, int count)
{
    int i1;
    int i2;

    i1 = 0;
    if (count % 3)
        return (0);
    while (tab[i1 + 1])
    {
        i2 = 0;
        while (tab[i1][i2] == tab[i1 + 1][i2] && tab[i1][i2] && tab[i1 + 1][i2])
            i2++;
        if (tab[i1][i2] > tab[i1 + 1][i2])
            return (0);
        i1++;
    }
    return (1);
}

void printer(char **strings)
{
    int index1;
    int index2;

    index1 = 0;
    while (strings[index1])
    {
        index2 = 0;
        while (strings[index1][index2])
        {
            if (strings[index1][index2 - 1] == '=')
                printf("%c", '"');
            printf("%c", strings[index1][index2]);
            index2++;
        }
        printf("%c\n", '"');
        index1++;
    }
}

void lexicographical_sort(char **env)
{
    char    *temp;
    int     iter1; 
    int     iter2;

    iter1 = 0;
    while (!is_sorted(env, iter1))
    {
        iter2 = 0;
        while (env[iter1][iter2] == env[iter1 + 1][iter2] 
                && env[iter1][iter2] && env[iter1 +1][iter2])
            iter2++;
        if (env[iter1 + 1][iter2] < env[iter1][iter2])
        {
            temp = env[iter1 + 1];
            env[iter1 + 1] = env[iter1];
            env[iter1] = temp;
        }
        iter1++;
        if (!env[iter1 + 1])
            iter1 = 0;
    }
    printer(env);
}

int ft_export(t_input *data)
{
    extern char **environ;
    if (!data->cmd_av[1])
        lexicographical_sort(environ);
    return (1);
}

int main()
{
    extern  char **environ; 
    int i = 0;
    while (environ[i])
        i++;
    environ[i] = "AAA1";
    environ[i + 1] = "AAA2";
    environ[i + 2] = "AAA3";
    environ[i + 3] = NULL;
    while (environ[i])
        i++;
    printf("size = %d\n", i);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:50:54 by midbella          #+#    #+#             */
/*   Updated: 2024/07/23 11:49:44 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_listdup(t_list *list)
{
	t_list	*head;
	t_list	*iter;

	head = ft_lstnew(ft_strdup(list->content));
	iter = head;
	list = list->next;
	while (list)
	{
		iter->next = ft_lstnew(ft_strdup(list->content));
		iter = iter->next;
		list = list->next;
	}
	return (head);
}

int	sort_helper(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] == str2[i] && str1[i] != '='
		&& str2[i] != '=')
		i++;
	if (str1[i] != '=' && str2[i] != '=' && str1[i] > str2[i])
		return (1);
	else if (str2[i] == '=' && str1[i] != '=')
		return (1);
	return (0);
}

void	swap_str(char **str1, char **str2, int *flag)
{
	char	*tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
	*flag = 1;
}

int	is_optoin(char *arg)
{
	int	index;

	index = 0;
	if (ft_strlen(arg) == 2 && arg[0] == '-' && arg[1] == 'n')
		return (1);
	else
		return (0);
}

void	set_old_pwd(t_holder *mem, char *old_pwd)
{
	char	*tab[3];
	char	**temp;

	tab[0] = "export";
	tab[1] = ft_strjoin("OLDPWD=", old_pwd);
	tab[2] = NULL;
	temp = mem->input->cmd_av;
	mem->input->cmd_av = tab;
	ft_export(mem, 1);
	mem->input->cmd_av = temp;
	free(tab[1]);
	free(old_pwd);
}

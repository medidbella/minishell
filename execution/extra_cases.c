/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:24:51 by midbella          #+#    #+#             */
/*   Updated: 2024/08/22 15:08:57 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_val(char *str)
{
	int	i;
	int	res;

	i = 1;
	if (str[0] != '-' && str[0] != '+' && !ft_isdigit(str[0]))
		return (1);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	if (is_big(str))
		return (ft_putstr_fd("warning: shell level too high, resetting to 1\n",
				2), 1);
	res = ft_atoi(str) + 1;
	if (res < 0)
		return (0);
	return (res);
}

char	**shell_lvl_helper(int sh_lvl)
{
	char	**res;
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_itoa(sh_lvl);
	tmp2 = ft_strjoin("export SHLVL=", tmp1);
	res = ft_split(tmp2, ' ');
	free(tmp1);
	free(tmp2);
	return (res);
}

void	set_shell_lvl(t_list	*envi)
{
	t_holder	mem;
	t_input		input;
	int			curr_lvl;
	int			i;

	i = 0;
	mem.pipes = NULL;
	mem.env = envi;
	mem.input = &input;
	while (envi)
	{
		if (!ft_strncmp(envi->content, "SHLVL=", 6))
			break ;
		envi = envi->next;
	}
	if (!envi)
		curr_lvl = 1;
	else
	{
		while (envi->content[i] && envi->content[i] != '=')
			i++;
		curr_lvl = get_val(&envi->content[i] + 1);
	}
	mem.input->cmd_av = shell_lvl_helper(curr_lvl);
	return (ft_export(&mem, 1), free_strings(mem.input->cmd_av));
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
}

void	set_pwd(t_holder *mem)
{
	char	*tab[3];
	char	*pwd;
	char	**temp;

	pwd = getcwd(NULL, PATH_MAX);
	free(g_status->cur_pwd);
	g_status->cur_pwd = ft_strdup(pwd);
	tab[0] = "export";
	tab[1] = ft_strjoin("PWD=", pwd);
	tab[2] = NULL;
	temp = mem->input->cmd_av;
	mem->input->cmd_av = tab;
	ft_export(mem, 1);
	mem->input->cmd_av = temp;
	free(tab[1]);
	free(pwd);
}

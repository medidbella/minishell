/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:01:24 by midbella          #+#    #+#             */
/*   Updated: 2024/07/16 19:04:54 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_glob	*g_memory;

int	builtins_or_external(t_input *cmd, char *bin_path)
{
	if (cmd->type == EXTERNAL)
	{
		execve(bin_path, cmd->cmd_av, NULL);
		return (print_error(ft_strjoin("command not found :", bin_path)), 127);
	}
	if (!strncmp("export", cmd->cmd_av[0], 6))
		return (ft_export(cmd, g_memory->env));
	else if (!strncmp("env", cmd->cmd_av[0], 6))
		return (ft_env(g_memory->env));
	else if (!strncmp("cd", cmd->cmd_av[0], 6))
		return (ft_cd(cmd));
	else if (!strncmp("pwd", cmd->cmd_av[0], 6))
		return (ft_pwd(cmd));
	else if (!strncmp("echo", cmd->cmd_av[0], 6))
		return (ft_echo(cmd));
	else if (!strncmp("unset", cmd->cmd_av[0], 6))
		return (ft_unset(cmd, &g_memory->env));
	return (0);
}

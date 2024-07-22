/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list_and_cmds_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:55:24 by alaktari          #+#    #+#             */
/*   Updated: 2024/07/22 10:42:07 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_built_in(t_input	*input)
{
	int		len;
	char	*cmd;

	if (input->cmd_av && input->cmd_av[0])
	{
		cmd = input->cmd_av[0];
		len = ft_strlen(cmd);
		if (((!ft_strncmp(cmd, "echo", len) && len == 4)) || ((!ft_strncmp(cmd,
						"pwd", len)) && len == 3) || ((!ft_strncmp(cmd,
						"export", len)) && len == 6)
			|| ((!ft_strncmp(cmd, "unset", len)) && len == 5)
			|| ((!ft_strncmp(cmd, "exit", len)) && len == 4)
			|| ((!ft_strncmp(cmd, "env", len)) && len == 3)
			|| ((!ft_strncmp(cmd, "cd", len)) && len == 2))
			input->type = BUILTIN;
		else
			input->type = EXTERNAL;
	}
	return (1);
}

int	input_or_output_valide(char *splited, int i)
{
	while (splited[i])
	{
		if (splited[i] == '<' )
			return (1);
		else if (splited[i] == '>')
			return (2);
		i++;
	}
	return (0);
}

int	input_redirection_or_her_doc(t_options *list, char *str, int len, int who)
{
	if (who == INPUT_RD)
	{
		list->input = malloc(sizeof(char) * len);
		if (!list->input)
			return (0);
		ft_strlcpy(list->input, str, len);
		list->who = INPUT_RD;
		list->out = NULL;
		list->limiter = NULL;
	}
	else
	{
		list->limiter = malloc(sizeof(char) * len);
		if (!list->limiter)
			return (0);
		ft_strlcpy(list->limiter, str, len);
		list->who = HERE_DOC;
		list->input = NULL;
		list->out = NULL;
	}
	return (1);
}

int	output_and_append_redirection(t_options *list, char *str, int len, int who)
{
	if (who == RD_TRNC)
	{
		list->out = malloc(sizeof(char) * len);
		if (!list->out)
			return (0);
		ft_strlcpy(list->out, str, len);
		list->who = RD_TRNC;
		list->input = NULL;
		list->limiter = NULL;
	}
	else
	{
		list->out = malloc(sizeof(char) * len);
		if (!list->out)
			return (0);
		ft_strlcpy(list->out, str, len);
		list->who = RD_APND;
		list->input = NULL;
		list->limiter = NULL;
	}
	return (1);
}

int	get_file_name_or_limiter(t_input *input, char *str,
			t_options *new_list, int who)
{
	int	len;
	int	x;

	new_list->next = NULL;
	len = ft_strlen(str) + 1;
	if (who == INPUT_RD)
		x = input_redirection_or_her_doc(new_list, str, len, INPUT_RD);
	else if (who == HERE_DOC)
		x = input_redirection_or_her_doc(new_list, str, len, HERE_DOC);
	else if (who == RD_TRNC)
		x = output_and_append_redirection(new_list, str, len, RD_TRNC);
	else
		x = output_and_append_redirection(new_list, str, len, RD_APND);
	if (!x)
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list_and_cmds_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:55:24 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/24 13:24:12 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	white_spaces(char *read_line)
{
	int	i;

	i = 0;
	while (read_line[i])
	{
		if (read_line[i] == '"')
		{
			i++;
			while (read_line[i] != '"')
				i++;
		}
		else if (read_line[i] == 39)
		{
			i++;
			while (read_line[i] != 39)
				i++;
		}
		else if ((read_line[i] >= 9 && read_line[i] <= 13)
			|| read_line[i] == 32)
			read_line[i] = ' ';
		i++;
	}
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
		if (do_expand(list->limiter))
			list->expand = 1;
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

int	get_file_name_or_limiter(char *str, t_options *new_list, int who)
{
	int	len;
	int	x;

	x = 0;
	new_list->next = NULL;
	len = ft_strlen(str) + 1;
	if (who == INPUT_RD || who == HERE_DOC)
		x = input_redirection_or_her_doc(new_list, str, len, who);
	else if (who == RD_TRNC || who == RD_APND)
		x = output_and_append_redirection(new_list, str, len, who);
	if (!x)
		return (0);
	return (1);
}

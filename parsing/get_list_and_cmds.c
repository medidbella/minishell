/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list_and_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:02:39 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/14 12:54:47 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_the_cmd(t_input *input, char *splited, int len, int i)
{
	char	*s1;
	char	*s2;
	int		x;

	x = 0;
	s1 = malloc(sizeof(char) * (len + 1));
	if (!s1)
		return (0);
	while (splited[i] == ' ')
		i++;
	if (!splited[i])
		return (free(s1), 1);
	while (splited[i])
		s1[x++] = splited[i++];
	s1[x] = '\0';
	s2 = ft_strdup(s1);
	if (!s2)
		return (free(s1), 0);
	input->cmd_av = ft_split(s2, ' ');
	if (!input->cmd_av)
		return (free(s2), free(s1), 0);
	return (free(s1), free(s2), 1);
}

int	get_input_and_output_file(t_input *input, char *splited, int who, int i)
{
	int			x;
	int			len;
	char		*str;
	t_options	*new_list;

	len = ft_strlen(splited) + 1;
	str = malloc(sizeof(char) * len);
	if (!str)
		return (-1);
	x = 0;
	if (splited[i] == '>' || splited[i] == '<')
		splited[i++] = ' ';
	if (splited[i] == ' ')
		i++;
	ft_cpy(splited, &i, str, &x);
	new_list = malloc(sizeof(t_options));
	if (!new_list)
		return (free(str), -1);
	if (!get_file_name_or_limiter(str, new_list, who))
		return (free(str), free(new_list), 0);
	return (lstadd_back(&input->list, new_list), free(str), i);
}

int	input_redirection_and_her_doc(t_input *input, char *splited, int i)
{
	int	who;

	who = HERE_DOC;
	while (splited[i])
	{
		while ((splited[i] == ' ' || splited[i] != '<') && splited[i])
			i++;
		if (splited[i] == '<' && splited[i + 1] != '<' && splited[i + 1])
			who = INPUT_RD;
		break ;
	}
	splited[i++] = ' ';
	if (who == INPUT_RD)
		i = get_input_and_output_file(input, splited, INPUT_RD, i);
	else
	{
		splited[i++] = ' ';
		i = get_input_and_output_file(input, splited, HERE_DOC, i);
	}
	if (i == -1)
		return (0);
	return (1);
}

int	output_redirection_and_append(t_input *input, char *splited, int i)
{
	int	who;

	who = RD_APND;
	while (splited[i])
	{
		while ((splited[i] == ' ' || splited[i] != '>') && splited[i])
			i++;
		if (splited[i] == '>' && splited[i + 1] && splited[i + 1] != '>')
			who = RD_TRNC;
		break ;
	}
	splited[i++] = ' ';
	if (who == RD_TRNC)
		i = get_input_and_output_file(input, splited, RD_TRNC, i);
	else
	{
		splited[i++] = ' ';
		i = get_input_and_output_file(input, splited, RD_APND, i);
	}
	if (i == -1)
		return (-1);
	return (i);
}

int	get_list_and_cmds(t_input *input, char *splited)
{
	int		i;
	int		check;
	int		find;

	i = 0;
	while (splited[i])
	{
		find = input_or_output_valide(splited, i);
		if (find == 1)
			check = input_redirection_and_her_doc(input, splited, i);
		else if (find == 2)
			check = output_redirection_and_append(input, splited, i);
		else
		{
			get_the_cmd(input, splited, ft_strlen(splited), 0);
			break ;
		}
		if (!check)
			return (0);
		if (splited[i + 1])
			i++;
	}
	return (1);
}

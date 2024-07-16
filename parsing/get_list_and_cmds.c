/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list_and_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:02:39 by alaktari          #+#    #+#             */
/*   Updated: 2024/07/16 17:49:14 by midbella         ###   ########.fr       */
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
		return (1);
	while (splited[i])
		s1[x++] = splited[i++];
	s1[x] = '\0';
	s2 = ft_strdup(s1);
	if (!s2)
		return (free(s1), 0);
	case_of_spaces_inside_double_quotes_1(s2);
	input->cmd_av = ft_split(s2, ' ');
	case_of_spaces_inside_double_quotes_2(input->cmd_av);
	remove_double_quotes(input->cmd_av, -1);
	if (!check_built_in(input))
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
	if (splited[i] == ' ')
		i++;
	while (splited[i] && splited[i] != ' ' && splited[i] != '>' && splited[i] != '<')
	{
		str[x++] = splited[i];
		splited[i++] = ' ';
	}
	str[x] = '\0';
	new_list = malloc(sizeof(t_options));
	if (!new_list)
		return (free(str), -1);
	x = get_file_name_or_limiter(input, str, new_list, who);
	if (!x)
		return (free(str), free(new_list), 0);
	return (lstadd_back(&input->list, new_list), free(str), i);
}

int	input_redirection_and_her_doc(t_input *input, char *splited, int i)
{
	int	who;

	while (splited[i])
	{
		while ((splited[i] == ' ' || splited[i] != '<') && splited[i])
			i++;
		if (splited[i] == '<' && splited[i + 1] != '<' && splited[i + 1])
			who = INPUT_RD;
		else if (splited[i] == '<' && splited[i + 1] == '<')
			who = HERE_DOC;
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

	while (splited[i])
	{
		while ((splited[i] == ' ' || splited[i] != '>') && splited[i])
			i++;
		if (splited[i] == '>' && splited[i + 1] && splited[i + 1] != '>')
			who = RD_TRNC;
		else if (splited[i] == '>' && splited[i + 1] == '>')
			who = RD_APND;
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

void	*get_list_and_cmds(t_input *input, char *splited)
{
	int		i;
	char	*str;
	int		check;

	i = 0;
	while (splited[i])
	{
		if (input_or_output_valide(splited, i) == 1)
			check = input_redirection_and_her_doc(input, splited, i);
		else if (input_or_output_valide(splited, i) == 2)
			check = output_redirection_and_append(input, splited, i);
		else
		{
			get_the_cmd(input, splited, ft_strlen(splited), 0);
			break ;
		}
		if (!check)
			return (NULL);
		if (splited[i + 1])
			i++;
	}
	return ((void *) input);
}

void	print_it(t_input *input)
{
	int i = 1;
	int x = 0;
	int y = 0;
	
	while (input)
	{
		printf("\n***************************************\n");
		printf("\nparent node number %d:\n", i);
		if (input->cmd_av)
		{
			if (input->cmd_av[x])
			{
				printf("cmd ==> [%s]", input->cmd_av[x]);
				if (input->type == BUILTIN)
					printf("       |< %s > |", "BUILTIN");
				else if (input->type == EXTERNAL)
					printf("       |< %s > |", "EXTERNAL");
				printf("\n");
				x++;
			}
			while (input->cmd_av[x])
			{
				printf("arguments : {%s}\n", input->cmd_av[x]);
				x++;
			}
		}
		printf("\n");
		while (input->list)
		{
			printf("who : %d\n", input->list->who);
			if (input->list->input)
				printf("input : {%s}\n", input->list->input);
			if (input->list->out)
				printf("out : {%s}\n", input->list->out);
			if (input->list->limiter)
				printf("limiter : {%s}\n", input->list->limiter);
			input->list = input->list->next;
			if (input->list)
				printf("------------------------------\n");
		}
		input = input->next;
		i++;
		x = 0;
	}
	printf("\n***************************************\n");
}

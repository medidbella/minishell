/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 20:50:07 by alaktari          #+#    #+#             */
/*   Updated: 2024/07/16 17:46:19 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fix_it(char **str, char *fixed_str, int i, int x)
{
	fixed_str = malloc(sizeof(char) * (ft_strlen(*str) + 1));
	if (!fixed_str)
		return (0);
	while ((*str)[i] == ' ' && (*str)[i])
		i++;
	while ((*str)[i])
	{
		if ((*str)[i] != ' ' && (*str)[i] != '"')
			fixed_str[x++] = (*str)[i++];
		else if ((*str)[i] == '"')
		{
			fixed_str[x++] = (*str)[i++];
			while ((*str)[i] != '"' && (*str)[i])
				fixed_str[x++] = (*str)[i++];
			fixed_str[x++] = (*str)[i++];
		}
		else if ((*str)[i] == ' ' && (*str)[i + 1] && (*str)[i + 1] != ' ')
			fixed_str[x++] = (*str)[i++];
		else
			i++;
	}
	fixed_str[x] = '\0';
	free((*str));
	*str = fixed_str;
	return (1);
}

void	set_input_struct(t_input *input)
{
	input->cmd_av = NULL;
	input->list = NULL;
	input->next = NULL;
	input->type = EXTERNAL;
}

t_input	*get_list_of_cmds(char **splited)
{
	int		i;
	t_input	*input;
	t_input	*new_input;

	i = -1;
	input = NULL;
	while (splited[++i])
	{
		new_input = malloc(sizeof(t_input));
		if (!new_input)
			return (free_t_inputs(input), NULL);
		set_input_struct(new_input);
		get_list_and_cmds(new_input, splited[i]);
		lstadd__back(&input, new_input);
	}
	return (input);
}

t_input	*ft_parsing(char *read_line)
{
	char	**splited;
	t_input	*input;
	int		i;

	i = 0;
	
	case_of_pipe_inside_quotes_1(read_line);
	splited = ft_split(read_line, '|');
	if (!splited)
		return (free(read_line), NULL);
	case_of_pipe_inside_quotes_2(splited);
	if (!remove_single_quotes(splited, -1, -1, 0))
		return (free(read_line), NULL);
	while (splited[i])
	{
		if (!fix_it(&splited[i], splited[i], 0, 0))
			return (free(read_line), free_splited(splited), NULL);
		i++;
	}
	input = get_list_of_cmds(splited);
	if (!input)
		return (free(read_line), free_splited(splited), NULL);
	return (input);
}


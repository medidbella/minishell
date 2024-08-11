/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 20:50:07 by alaktari          #+#    #+#             */
/*   Updated: 2024/08/09 16:37:15 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft__cpy(char *fixed_str, int *x, char *str, int *i)
{
	fixed_str[(*x)++] = str[(*i)++];
	while (str[(*i)] != '"' && str[(*i)])
		fixed_str[(*x)++] = str[(*i)++];
	fixed_str[(*x)++] = str[(*i)++];
}

static int	fix_it(char **str, char *fixed_str, int i, int x)
{
	fixed_str = malloc(sizeof(char) * (ft_strlen(*str) + 1));
	if (!fixed_str)
		return (0);
	while ((*str)[i] == ' ' && (*str)[i])
		i++;
	if (!(*str)[i])
		return (free(fixed_str), 0);
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && (*str)[i + 1] == '"')
			i++;
		if ((*str)[i] != ' ' && (*str)[i] != '"' && (*str)[i])
			fixed_str[x++] = (*str)[i++];
		else if ((*str)[i] == '"' && (*str)[i])
			ft__cpy(fixed_str, &x, *str, &i);
		else if ((*str)[i] == ' ' && (*str)[i + 1] && (*str)[i + 1] != ' ')
			fixed_str[x++] = (*str)[i++];
		else
			i++;
	}
	fixed_str[x] = 0;
	free((*str));
	(*str = fixed_str);
	return (1);
}

static t_input	*get_list_of_cmds(char **splited)
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
			return (free_splited(splited), NULL);
		new_input->cmd_av = NULL;
		new_input->list = NULL;
		new_input->next = NULL;
		if (!get_list_and_cmds(new_input, splited[i]))
			return (free(new_input), free_splited(splited), NULL);
		lstadd__back(&input, new_input);
	}
	return (free_splited(splited), input);
}

char	**split_read_line(char *read_line)
{
	char	**splited;
	int		i;

	i = -1;
	if (!ft_errors(read_line))
		return (NULL);
	case_of_pipe_inside_quotes_1(read_line);
	splited = ft_split(read_line, '|');
	if (!splited)
		return (NULL);
	case_of_pipe_inside_quotes_2(splited);
	if (!quotes_cases_1(splited))
		return (free_splited(splited), NULL);
	while (splited[++i])
	{
		if (!fix_it(&splited[i], splited[i], 0, 0))
			return (free_splited(splited), NULL);
	}
	return (splited);
}

t_input	*ft_parsing(char *read_line, t_list *env)
{
	char	**splited;
	t_input	*input;
	int		i;

	i = -1;
	splited = split_read_line(read_line);
	if (!splited)
		return (NULL);
	input = get_list_of_cmds(splited);
	if (!input)
		return (NULL);
	if (!expansion(input, env, -1))
		return (free_inputs(input), NULL);
	if (!quotes_cases_2(input))
		return (free_inputs(input), NULL);
	skip_spaces_for_echo_args(input);
	return (input);
}

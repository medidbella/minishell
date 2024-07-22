/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 20:50:07 by alaktari          #+#    #+#             */
/*   Updated: 2024/07/22 10:42:51 by alaktari         ###   ########.fr       */
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
		if ((*str)[i] == '$' && (*str)[i + 1] == '"')
			i++;
		if ((*str)[i] != ' ' && (*str)[i] != '"' && (*str)[i])
			fixed_str[x++] = (*str)[i++];
		else if ((*str)[i] == '"' && (*str)[i])
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
	return (fixed_str[x] = 0, free((*str)), (*str = fixed_str), 1);
}

void	set_input_struct(t_input *input)
{
	input->cmd_av = NULL;
	input->list = NULL;
	input->next = NULL;
}

t_input	*get_list_of_cmds(char **splited, t_list *env)
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
			return (NULL);
		set_input_struct(new_input);
		get_list_and_cmds(new_input, splited[i], env);
		lstadd__back(&input, new_input);
	}
	return (input);
}

t_input	*ft_parsing(char *read_line, t_list *env)
{
	char	**splited;
	t_input	*input;
	int		i;

	i = -1;
	case_of_pipe_inside_quotes_1(read_line);
	splited = ft_split(read_line, '|');
	if (!splited)
		return (free(read_line), NULL);
	case_of_pipe_inside_quotes_2(splited);
	if (!remove_single_quotes(splited, -1, -1, 0))
		return (free(read_line), NULL);
	while (splited[++i])
	{
		if (!fix_it(&splited[i], splited[i], 0, 0))
			return (free(read_line), free_splited(splited), NULL);
	}
	i = 0;
	input = get_list_of_cmds(splited, env);
	if (!input)
		return (free(read_line), free_splited(splited), NULL);
	free_splited(splited);
	if (!expansion(input, env, -1))
		return (free_inputs(input), free(read_line), NULL);
	return (return_dollar_sign(input), free(read_line), input);
}

// t_list *get_listiroments(void)
// {
// 	t_list *env = malloc(sizeof(t_list));
// 	t_list *head = env;

// 	env->content = ft_strdup("var=cat");
// 	env->next = malloc(sizeof(t_list));
// 	env->next->content = ft_strdup("arg=-e");
// 	env->next->next = malloc(sizeof(t_list));
// 	env->next->next->content = ft_strdup("out=put_file");
// 	env->next->next->next = NULL;
// 	return
// 	(env);
// }

// void free_env(t_list *env)
// {
// 	t_list *next;

// 	while (env)
// 	{
// 		next = env->next;
// 		free(env->content);
// 		free(env);
// 		env = next;
// 	}
// }

// int main()
// {
// 	t_input *input;
// 	t_list	*env;
// 	char	*read_line;

// 	while (1)
// 	{
// 		char s[] = "\e[31m➜  \e[36mMiniShell\e[0m ";
// 		read_line = readline("MINISHELL : ");
// 		if (!read_line)
// 			return (1);
// 		add_history(read_line);
// 		env = get_listiroments();
// 		input = ft_parsing(read_line, env);
// 		if (!input)
// 			return (1);
// 		print_it(input);
// 		free_inputs(input);
// 		free_env(env);
// 	}
// }

//  $VAR
// ---------

/// "VAR=123"   ==> change
/// NULL        ===> remove
// "VAR"
// "VAR=
/*    "$var"  ==>   cat
	  $"var"  ==>   var
	  -----------------
      '$var'  ==>   $var
	  $'var'  ==>   var
*/
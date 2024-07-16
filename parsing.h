/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:39:39 by midbella          #+#    #+#             */
/*   Updated: 2024/07/14 18:46:02 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_input t_input;
typedef struct s_options t_options;
typedef struct s_list t_list;

void	free_splited(char **splited);
void	free_list(t_options *list);
void	free_t_inputs(t_input *head);
void	*get_list_and_cmds(t_input *input, char *splited);
void	print_it(t_input *input);
int		lstsize(t_options *lst);
t_options	*lstlast(t_options *lst);
void	lstadd_back(t_options **lst, t_options *new_node);
t_input	*lst_last(t_input *head);
void	lstadd__back(t_input **input, t_input *new_node);
int	input_or_output_valide(char *splited, int i);
int		input_redirection_or_her_doc(t_options *list, char *str,
			int len, int who);
int		output_and_append_redirection(t_options *list, char *str,
			int len, int who);
int		get_file_name_or_limiter(t_input *input, char *str,
			t_options *new_list, int who);
void	case_of_pipe_inside_quotes_1(char *read_line);
void	case_of_pipe_inside_quotes_2(char **splited);
int		remove_single_quotes(char **splited, int i, int x, int y);
void	case_of_spaces_inside_double_quotes(char *splited);
int	remove_double_quotes(char **cmd_av, int i);
void	case_of_spaces_inside_double_quotes_1(char *s2);
void	case_of_spaces_inside_double_quotes_2(char **cmd_av);
int	check_built_in(t_input	*input);
t_input	*ft_parsing(char *read_line);
#endif
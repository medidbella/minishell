/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:39:39 by midbella          #+#    #+#             */
/*   Updated: 2024/07/24 18:33:03 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_input t_input;
typedef struct s_options t_options;
typedef struct s_list t_list;

typedef struct s_expnd
{
	t_list			*env;
	int				var_len;
	int				value_len;
	int				exist;
	char			*var;
	struct s_expnd	*next;
}	t_expnd;

t_input		*ft_parsing(char *read_line, t_list *env);
void		free_inputs(t_input *input);
void		free_splited(char **splited);
void		*get_list_and_cmds(t_input *input, char *splited, t_list *env);
void		print_it(t_input *input);
int			lstsize(t_options *lst);
t_options	*lstlast(t_options *lst);
void		lstadd_back(t_options **lst, t_options *new_node);
t_input		*lst_last(t_input *head);
void		lstadd__back(t_input **input, t_input *new_node);
int			input_or_output_valide(char *splited, int i);
int			input_redirection_or_her_doc(t_options *list, char *str,
				int len, int who);
int			output_and_append_redirection(t_options *list, char *str,
				int len, int who);
int			get_file_name_or_limiter(t_input *input, char *str,
				t_options *new_list, int who);
void		case_of_pipe_inside_quotes_1(char *read_line);
void		case_of_pipe_inside_quotes_2(char **splited);
int			remove_single_quotes(char **splited, int i, int x, int y);
void		case_of_spaces_inside_double_quotes(char *splited);
int			remove_double_quotes(char **cmd_av, int i);
void		case_of_spaces_inside_double_quotes_1(char *s2);
void		case_of_spaces_inside_double_quotes_2(char **cmd_av);
int			check_built_in(t_input	*input);
char		*ft_expansion(char *read_line, t_list *env, int i, t_expnd *expnd);
t_expnd		*ft_lst_new(void);
t_expnd		*ft_lst_last(t_expnd *lst);
void		ft_lst_add_back(t_expnd **lst, t_expnd *new);
int			get_the_len(t_expnd *expnd, int read_line_len);
void		ft_infos(t_list *env, t_expnd *expnd, char *var);
int			expansion(t_input *input, t_list *env, int i);
void		get_infos_2(t_expnd *expnd, char *read_line, char *var, int x);
int			expansion_for_list(t_options *list, t_list *env);
int			if_not_exists(t_expnd *expnd, char *new_str, int *j, int *x);
void		return_dollar_sign(t_input *input);
void		free_expnd(t_expnd *expnd);
#endif
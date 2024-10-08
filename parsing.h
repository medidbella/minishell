/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:39:39 by midbella          #+#    #+#             */
/*   Updated: 2024/08/24 17:14:16 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_input		t_input;
typedef struct s_options	t_options;
typedef struct s_list		t_list;

# define S_QUOTES -1
# define D_QUOTES -2
# define DOLLAR -3
# define SPACES -4
# define NOT_EXIST -5
# define EXIT_STATUS -6
# define REMOVE -7
# define IN_RED -8
# define OUT_RED -9

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
int			ft_errors(char *read_line);
int			redirection_errors(char *read_line);
int			print_errors(int which);
void		free_inputs(t_input *input);
void		free_splited(char **splited);
void		free_env(t_list *env);
int			get_list_and_cmds(t_input *input, char *splited);
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
int			get_file_name_or_limiter(char *str, t_options *new_list, int who);
void		case_of_pipe_inside_quotes_1(char *read_line);
int			pipe_errors_2(char *read_line, int i, int x, int chaecker);
void		case_of_pipe_inside_quotes_2(char **splited);
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
void		no_expand(char **ptr);
void		replace_special_chars(char *p_to_char);
int			if_not_exists(t_expnd *expnd, char *new_str, int *x);
void		ft_cpy(char *splited, int *i, char *str, int *x);
void		free_expnd(t_expnd *expnd);
int			quotes_cases_1(char **splited);
int			quotes_cases_2(t_input *input);
int			remove_quotes(t_input *input, t_input *head);
char		*start_removing(char *splited);
void		case_of_dollar_sign(char *splited);
void		case_of_exit_statu(char *splited);
int			check_if_var_is_not_exist(t_input *input, t_input *head,
				int i, int x);
char		*get_return_value(char *curr_str);
int			split_cmds_and_args(t_input *input, t_input *head, int i, int size);
char		*get_splited_arg(char *arg);
void		tabs_to_spaces(char *arg, int i);
int			len_of_splited_arg(char **splited_arg);
void		swap_args(t_input *input);
void		check_list(t_options *list);
void		free_empty_strs(t_input *input);
void		return_to_spaces(char **splited);
void		white_spaces(char *read_line);
int			no_remove(char *str);
int			get_cmd_av_size(char **cmd_av);
int			more_than_a_word(char *str);
int			get_the_new_len(char *str);
int			ft_specials(char c, int who);
void		there_are_specials(char *str, int i);
int			limiter_chars(char c);
int			only_special_chars(char *str);
int			special_and_normale_chars(char *s);
int			remove_special_chars(char **str);
void		replace_special_chars(char *p_to_char);
int			do_expand(char *limiter);

#endif
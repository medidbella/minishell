/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:39:41 by midbella          #+#    #+#             */
/*   Updated: 2024/07/24 21:41:34 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_input		t_input;
typedef struct s_options	t_options;
typedef struct s_list		t_list;
typedef struct s_holder		t_holder;

void	free_strings(char **strs);
char	*find_path(char *find_me, t_list *env);
void	close_and_free_pipes(int **fds);
t_list	*envron_dup(char **environ);
void	swap_str(char **str1, char **str2, int *flag);
void	lst_free(t_list *list);
void	printer(t_list *head, int write_fd);
void	print_error(char *str);
t_list	*ft_listdup(t_list *list);
int		sort_helper(char *str1, char *str2);
int		double_quotes(char *str);
int		ft_echo(t_holder *mem, int write_fd);
int		ft_pwd(t_holder *mem, int write_fd);
int		ft_cd(t_holder *mem, char *curr_dir);
int		ft_env(t_holder *mem, int write_fd);
int		ft_unset(t_input *data, t_list **env);
int		ft_exit(t_holder *mem);
int		is_optoin(char *arg);
int		here_doc(t_holder *mem, char *delimiter, int write_fd);
void	here_doc_sim(char *delimiter);
int		ft_export(t_holder *mem, int write_fd);
int		var_finder(t_list *env, char *var);
void	error_detector(char *av, int *return_val);
int		inputs_count(t_input *inpt_list);
int		global_exec(t_holder *mem);
char	**prep_env(t_list *env);
void	open_failer(char *err_msg, char *file);
int		ft_sorter(t_input *cmd_node, int *write_idx,
			int *read_idx, int *here_doc);
void	_write(t_options *list, int *last_w, int *last_r);
void	case_of_error(t_options *tst_node, int *flag);
void	set_read_write(t_options *list, int *last_w, int *last_r);
int		get_input_output(t_options *iter, int *node_idx, int *her_doc);
int		executer(t_holder *mem, int w_fd, int r_fd);
int		**pipes_creator(int number);
void	pipe_or_option(int *write_idx, int *read_idx,
			int *pipe_wfd, int *pipe_rfd);
void	close_unused_pipes(int **pipes, int w_fd, int r_fd);
int		exec_builtin(t_holder *mem, int write_fd, int read_fd);
char	*ft_get_env(char *var, t_list *env);
void	set_old_pwd(t_holder *mem, char *old_pwd);
void	child_mem_free(t_holder *mem, char **child_env);
#endif
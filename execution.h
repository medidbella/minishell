/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:39:41 by midbella          #+#    #+#             */
/*   Updated: 2024/08/24 20:58:03 by midbella         ###   ########.fr       */
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
void	lstfree(t_list *list);
void	printer(t_list *head, int write_fd, int index, int flag);
void	print_error(char *str);
t_list	*ft_listdup(t_list *list);
int		sort_helper(char *str1, char *str2);
void	child_sigquit_handler(int sig);
int		ft_echo(t_holder *mem, int write_fd);
int		ft_pwd(t_holder *mem, int write_fd);
int		ft_cd(t_holder *mem, char *curr_dir);
int		ft_env(t_holder *mem, int write_fd);
int		ft_unset(t_input *data, t_list **env);
int		ft_exit(t_holder *mem);
int		is_optoin(char *arg);
int		here_doc(t_holder *mem, t_options *list, int index);
int		ft_export(t_holder *mem, int write_fd);
int		var_finder(t_list *env, char *var);
void	error_detector(char *av, int *return_val);
int		inputs_count(t_input *inpt_list);
int		global_exec(t_holder *mem);
void	cd_child_case(t_holder *mem, char *path);
char	**prep_env(t_list *env);
void	open_failer(char *err_msg, char *file);
int		log_file_create(int *fds, int index);
int		ft_sorter(t_holder *mem, int *write_idx, int *read_idx);
int		set_file_descriptors(t_holder *mem, int *pipe_wfd, int *pipe_rfd);
int		set_here_doc_fds(t_holder *mem);
void	check_validity(t_options *tst_node, int *flag);
void	set_read_write(t_options *list, int *last_w, int *last_r);
int		get_input_output(t_options *iter, int *node_idx);
void	prep_exeve(t_holder *mem, int w_fd, int r_fd, char *bin_path);
void	executer(t_holder *mem, int w_fd, int r_fd);
int		execve_failure(char *cmd, int *r_val);
int		**pipes_creator(int number);
void	pipe_or_option(int *write_idx, int *read_idx,
			int *pipe_wfd, int *pipe_rfd);
void	close_unused_pipes(int **pipes, int w_fd, int r_fd);
int		exec_builtin(t_holder *mem, int write_fd, int read_fd);
char	*ft_get_env(char *var, t_list *env);
void	set_pwd(t_holder *mem);
void	set_old_pwd(t_holder *mem, char *old_pwd);
int		opt_iter(t_holder *mem, int *write_idx, int *read_idx);
void	child_mem_free(t_holder *mem, char **child_env);
void	set_shell_lvl(t_list	*envi);
void	sigint_handler(int sig);
int		locate_char(char *str, char c);
void	ignore_signals(char *cmd);
void	here_doc_wait(int pid);
void	child_sigint(int sig);
void	here_doc_sigint(int sig);
char	*get_new_line(char *new_line, t_list *env);
int		is_dir(char *path);
void	her_doc_parent_sigint(int sig);
int		is_numeric(char *str);
void	init_vars(int *a, int *b, int *c);
void	log_msg(char *dir, int write_fd);
void	ft_close(int fd);
int		custome_strlen(char *str);
int		is_big(char *str);

#endif

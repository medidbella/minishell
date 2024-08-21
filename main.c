/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:27:15 by midbella          #+#    #+#             */
/*   Updated: 2024/08/21 14:04:11 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	*g_status;

void	init_struct(t_holder *block, char **envp, t_sig *info, char **av)
{
	info->prog_name = av[0];
	block->env = NULL;
	block->pipes = NULL;
	block->input = NULL;
	g_status = info;
	info->r_val = 0;
	info->cur_pwd = NULL;
	block->env = envron_dup(envp);
	set_shell_lvl(block->env);
}

int	main(int ac, char **av, char **envp)
{
	char		*read_line;
	t_holder	block;
	t_sig		info;

	if (ac > 1)
		return (ft_putstr_fd("arguments are not allowed\n", 2), 1);
	init_struct(&block, envp, &info, av);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint_handler);
		read_line = readline("MINISHELL : ");
		if (!read_line)
			return (free(g_status->cur_pwd), lstfree(block.env),
				write(2, "exit\n", 5), g_status->r_val);
		add_history(read_line);
		g_status->stp_flag = 0;
		block.input = ft_parsing(read_line, block.env);
		block.input_head = block.input;
		free(read_line);
		signal(SIGQUIT, child_sigquit_handler);
		signal(SIGINT, child_sigint);
		global_exec(&block);
		free_inputs(block.input_head);
	}
}

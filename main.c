/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:27:15 by midbella          #+#    #+#             */
/*   Updated: 2024/07/29 19:10:38 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	*r_val;

int	main(int ac, char **av, char **envp)
{
	t_holder	block;
	t_list		*environment;
	char		*read_line;

	r_val = &block.last_r_val;
	environment = envron_dup(envp);
	set_shell_lvl(environment);
	block.env = environment;
	block.last_r_val = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
 	while (1)
	{
		read_line = readline("MINISHELL : ");
		if (!read_line)
			return (write(1, "exit\n", 5), 0);
		add_history(read_line);
		block.input = ft_parsing(read_line, environment);
		global_exec(&block);
		free_inputs(block.input);
	}
}

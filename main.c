/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:27:15 by midbella          #+#    #+#             */
/*   Updated: 2024/07/22 10:47:52 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_holder	block;
	t_list		*environment;
	char		*read_line;

	environment = envron_dup(envp);
	block.env = environment;
	block.last_r_val = 0;
	// signal(SIGINT, rl_on_new_line);
	while (1)
	{
		read_line = readline("MINISHELL : ");
		if (!read_line)
			return (1);
		add_history(read_line);
		block.input = ft_parsing(read_line, environment);
		global_exec(&block);
		free_inputs(block.input);
	}
}

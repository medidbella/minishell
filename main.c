/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:27:15 by midbella          #+#    #+#             */
/*   Updated: 2024/07/26 13:32:43 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int ac, char **av, char **envp)
{
	t_holder	block;
	t_list		*environment;
	char		*read_line;

	environment = envron_dup(envp);
	set_shell_lvl(environment);
	block.env = environment;
	block.last_r_val = 0;
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

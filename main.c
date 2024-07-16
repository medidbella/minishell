/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:27:15 by midbella          #+#    #+#             */
/*   Updated: 2024/07/16 19:06:13 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob	*g_memory;

int	main(int ac, char **av, char **envp)
{
	t_glob	shared;
	t_list	*environment;
	t_input	*input;
	char	*read_line;

	environment = envron_dup(envp);
	shared.env = environment;
	g_memory = &shared;
	while (1)
	{
		read_line = readline("MINISHELL : ");
		if (!read_line)
			return (1);
		add_history(read_line);
		input = ft_parsing(read_line);
		global_exec(input);
	}
}

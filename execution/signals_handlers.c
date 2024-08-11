/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:36:16 by midbella          #+#    #+#             */
/*   Updated: 2024/08/11 21:15:33 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_sig	*g_status;

void	child_sigint(int sig)
{
	sig *= 1;
	write(1, "\n", 1);
	exit(130);
}

void	sigint_handler(int sig)
{
	sig *= 1;
	g_status->r_val = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	here_doc_sigint(int sig)
{
	sig *= 1;
	g_status->r_val = 130;
	exit(1);
}

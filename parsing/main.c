/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:30:18 by midbella          #+#    #+#             */
/*   Updated: 2024/07/03 10:22:17 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main()
{
    t_list  *environment;
    char    *input;
    char    *prompt;


    prompt = getenv("USER");
    input = readline(prompt);
    environment = envron_dup();
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:01:08 by midbella          #+#    #+#             */
/*   Updated: 2024/07/29 16:10:39 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PATH_MAX 3000 // tmp to scilence error 
# define RD_TRNC 1 // > 
# define RD_APND 2 // >>
# define HERE_DOC 3 // <<
# define INPUT_RD 4 // <
# define EXTERNAL 13
# define BUILTIN 37

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>
# include "execution.h"
# include "parsing.h"
# include "libft/libft.h"


typedef struct s_options
{
	char				*input;
	char				*out;
	char				*limiter;
	int					who;
	struct s_options	*next;
}	t_options;

typedef struct s_input
{
	char			**cmd_av;
	int				type;
	t_options		*list;
	struct s_input	*next;
}	t_input;

typedef struct s_holder
{
	t_input 		*input;
	t_list			*env;
	int				**pipes;
	unsigned char	last_r_val;
}	t_holder;
#endif
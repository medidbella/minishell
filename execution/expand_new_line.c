/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_new_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:36:36 by midbella          #+#    #+#             */
/*   Updated: 2024/08/12 20:15:06 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	replace_quotes(char *new_line, int who)
{
	int	i;

	i = 0;
	if (who == 1)
	{
		while (new_line[i])
		{
			if (new_line[i] == '"')
				new_line[i] = D_QUOTES;
			else if (new_line[i] == 39)
				new_line[i] = S_QUOTES;
			i++;
		}
		return ;
	}
	while (new_line[i])
	{
		if (new_line[i] == D_QUOTES)
			new_line[i] = '"';
		else if (new_line[i] == S_QUOTES)
			new_line[i] = 39;
		i++;
	}
}

static char	*remove__quotes(char *new_line)
{
	int	i;

	i = 0;
	while (new_line[i])
	{
		if (new_line[i] == 39)
		{
			new_line[i++] = REMOVE;
			while (new_line[i] != 39)
				i++;
			new_line[i] = REMOVE;
		}
		else if (new_line[i] == '"')
		{
			new_line[i++] = REMOVE;
			while (new_line[i] != '"')
				i++;
			new_line[i] = REMOVE;
		}
		i++;
	}
	new_line = start_removing(new_line);
	if (!new_line)
		return (NULL);
	return (new_line);
}

char	*if_var_not_exists(char *new_line)
{
	char	*new;

	new = new_line;
	if (new_line[0] == NOT_EXIST)
	{
		free(new_line);
		new = ft_strdup("");
		if (!new)
			return (NULL);
	}
	return (new);
}

char	*get_new_line(char *new_line, t_list *env)
{
	char	*new;

	replace_quotes(new_line, 1);
	new = ft_expansion(new_line, env, 0, NULL);
	if (!new)
		return (NULL);
	new = remove__quotes(new);
	if (!new)
		return (NULL);
	replace_quotes(new, 2);
	return (if_var_not_exists(new));
}

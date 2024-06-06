/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:01:53 by midbella          #+#    #+#             */
/*   Updated: 2023/11/26 23:10:31 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**strs_free(char **strings, int i)
{
	while (i >= 0)
	{
		free(strings[i]);
		i--;
	}
	free (strings);
	return (NULL);
}

static char	*str_filler(const char *s, int end, char c)
{
	char	*str;
	int		start;
	int		len;

	start = end;
	while (s[start] != c && start >= 0)
		start--;
	len = end - start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = s[end];
		len--;
		end--;
	}
	return (str);
}

static int	word_count(const char *s, char c)
{
	int	i;
	int	word_nb;

	word_nb = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			word_nb++;
		i++;
	}
	return (word_nb);
}

static int	end_index(const char *s, char c, int i)
{
	if (s[0] != c && s[1] == c && i == 0)
		return (0);
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i])
	{
		if (s[i + 1] == c || s[i + 1] == '\0')
			return (i);
	i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		strnum;
	int		i;
	int		end;
	char	**strings;

	if (!s)
		return (NULL);
	i = 0;
	end = end_index(s, c, 0);
	strnum = word_count(s, c);
	strings = malloc(sizeof(char *) * (strnum + 1));
	if (!strings)
		return (NULL);
	while (i < strnum)
	{
		strings[i] = str_filler(s, end, c);
		if (!strings[i])
			return (strs_free(strings, i - 1));
		end = end_index(s, c, end + 1);
		i++;
	}
	strings[i] = NULL;
	return (strings);
}

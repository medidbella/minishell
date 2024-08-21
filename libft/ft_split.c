/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaktari <alaktari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:01:53 by midbella          #+#    #+#             */
/*   Updated: 2024/08/20 16:36:40 by alaktari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_counter(char *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static size_t	word_len(char *s, char c, size_t index)
{
	size_t	i;
	size_t	my_index;

	i = index;
	my_index = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		my_index++;
	}
	return (my_index);
}

static char	*ft_strdup_word(char *s, char c, size_t index)
{
	size_t	i;
	size_t	str_len;
	char	*word;

	str_len = word_len(s, c, index);
	word = malloc(sizeof(char) * (str_len + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < str_len)
	{
		word[i] = s[index + i];
		i++;
	}
	word[str_len] = '\0';
	return (word);
}

static char	**ft_free_split(char **str_split)
{
	size_t	i;

	i = 0;
	while (str_split[i])
	{
		free(str_split[i]);
		i++;
	}
	free(str_split);
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	size_t	words_count;
	size_t	iindex;
	size_t	str_alloc;
	char	**str_split;

	if (s == NULL)
		return (NULL);
	iindex = 0;
	str_alloc = 0;
	words_count = ft_word_counter(s, c);
	str_split = malloc(sizeof(char *) * (words_count + 1));
	if (!(str_split))
		return (NULL);
	while (words_count-- > 0)
	{
		while (s[iindex] == c)
			iindex++;
		str_split[str_alloc++] = ft_strdup_word(s, c, iindex);
		if (str_split[str_alloc - 1] == NULL)
			return (ft_free_split(str_split));
		iindex += word_len(s, c, iindex);
	}
	str_split[str_alloc] = NULL;
	return (str_split);
}

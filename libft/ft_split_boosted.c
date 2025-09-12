/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_boosted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:05:54 by kiteixei          #+#    #+#             */
/*   Updated: 2025/06/30 03:13:28 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_charset(str[i], charset))
			i++;
		if (str[i] && !is_charset(str[i], charset))
		{
			count++;
			while (str[i] && !is_charset(str[i], charset))
				i++;
		}
	}
	return (count);
}

static char	*alloc_word(char *str, int start, int end)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	free_split(char **res, int j)
{
	while (j > 0)
		free(res[--j]);
	free(res);
}

static int	fill_split(char **res, char *str, char *charset)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && is_charset(str[i], charset))
			i++;
		start = i;
		while (str[i] && !is_charset(str[i], charset))
			i++;
		if (start < i)
		{
			res[j] = alloc_word(str, start, i);
			if (!res[j])
				return (free_split(res, j), 0);
			j++;
		}
	}
	res[j] = NULL;
	return (1);
}

char	**ft_split_boosted(char *str, char *charset)
{
	char	**res;
	int		word_count;

	if (!str || !charset)
		return (NULL);
	word_count = count_words(str, charset);
	res = malloc(sizeof(char *) * (word_count + 1));
	if (!res)
		return (NULL);
	if (!fill_split(res, str, charset))
		return (NULL);
	return (res);
}

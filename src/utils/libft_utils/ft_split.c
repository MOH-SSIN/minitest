/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:50:54 by idahhan           #+#    #+#             */
/*   Updated: 2025/05/23 12:50:55 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	count_word(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			count++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*copy_word(const char *s, int start, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)ft_malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_split(char **result, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

static int	fill_words(char **result, const char *s, char c, int index)
{
	int	start;
	int	len;
	int	i;

	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			len = i - start;
			result[index] = copy_word(s, start, len);
			if (!result[index])
			{
				free_split(result, index - 1);
				return (-1);
			}
			index++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**result;
	int		index;

	index = 0;
	if (!s)
		return (NULL);
	word_count = count_word(s, c);
	result = (char **)ft_malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (fill_words(result, s, c, index) == -1)
		return (NULL);
	result[word_count] = NULL;
	return (result);
}

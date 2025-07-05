/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:31:43 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/21 09:46:08 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	if (!dest || !src)
		return (dest);
	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

static char	*create_space_token(void)
{
	char	*space;

	space = ft_malloc(2);
	space[0] = ' ';
	space[1] = '\0';
	return (space);
}

static char	*create_word_token(const char *str, int start, int end)
{
	char	*word;
	int		len;

	len = end - start;
	word = ft_malloc(len + 1);
	ft_strncpy(word, str + start, len);
	word[len] = '\0';
	return (word);
}

char	**split_words_and_spaces(const char *str)
{
	char	**result;
	int		i;
	int		j;
	int		start;

	(1) && (i = 0, j = 0);
	if (!str)
		return (NULL);
	result = ft_malloc((ft_strlen(str) + 2) * sizeof(char *));
	while (str[i])
	{
		if (str[i] == ' ')
			result[j++] = create_space_token();
		else
		{
			start = i;
			while (str[i] && str[i] != ' ')
				i++;
			result[j++] = create_word_token(str, start, i);
			continue ;
		}
		i++;
	}
	result[j] = NULL;
	return (result);
}

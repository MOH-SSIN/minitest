/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:09:36 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/20 20:13:47 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	search_hrd(t_token_node *debut)
{
	while (debut)
	{
		if (debut->type == HEREDOC)
			return (1);
		debut = debut->next;
	}
	return (0);
}

int	ft_count_wrd(char *str)
{
	int	i;
	int	wc;

	wc = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_espace(str[i]))
			i++;
		if (str[i])
			wc++;
		while (str[i] && !is_espace(str[i]))
			i++;
	}
	return (wc);
}

char	*ft_strncpy(char *str1, char *str2, int n)
{
	int	i;

	i = 0;
	while (str2[i] && i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
	return (str1);
}

char	**tab_word(char **tab, char *str)
{
	int	start;
	int	end;
	int	word_index;
	int	word_len;

	word_index = 0;
	word_len = 0;
	(1) && (start = 0, end = 0);
	while (str[end])
	{
		while (str[end] && is_espace(str[end]))
			end++;
		start = end;
		while (str[end] && !is_espace(str[end]))
			end++;
		if (end > start)
		{
			word_len = end - start;
			tab[word_index] = (char *)ft_malloc(word_len + 1);
			ft_strncpy(tab[word_index], &str[start], word_len);
			word_index++;
		}
	}
	tab[word_index] = NULL;
	return (tab);
}

char	**ft_decoupe_en_mots(char *token_value)
{
	char	**tab;
	int		count_wrd;

	if (!token_value)
		return (NULL);
	count_wrd = ft_count_wrd(token_value);
	tab = (char **)ft_malloc(sizeof(char *) * (count_wrd + 1));
	return (tab_word(tab, token_value));
}

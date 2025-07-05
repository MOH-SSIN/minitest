/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:13:44 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/05/18 17:19:54 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	ft_trouver(char c, const char *set2)
{
	while (*set2)
	{
		if (*set2 == c)
			return (1);
		set2++;
	}
	return (0);
}

static int	ft_index_debut(const char *s1, const char *set)
{
	int	debut;

	debut = 0;
	while (s1[debut] && ft_trouver(s1[debut], set))
		debut++;
	return (debut);
}

static int	ft_index_fin(const char *s1, const char *set)
{
	int	fin;

	fin = ft_strlen(s1) - 1;
	while (fin > 0 && ft_trouver(s1[fin], set))
		fin--;
	return (fin);
}

static char	*ft_new_chaine(char *ptr, const char *s1, int debut, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
		ptr[i] = s1[debut + i];
	ptr[len] = '\0';
	return (ptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		debut;
	int		fin;
	size_t	len;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	if (!(*s1))
	{
		ptr = ft_malloc(sizeof(char) * 1);
		if (!ptr)
			return (NULL);
		*ptr = 0;
		return (ptr);
	}
	debut = ft_index_debut(s1, set);
	fin = ft_index_fin(s1, set);
	if (debut > fin)
		return (ft_strdup(""));
	len = fin - debut + 1;
	ptr = (char *)ft_malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	return (ft_new_chaine(ptr, s1, debut, len));
}

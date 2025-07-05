/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:18:30 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/05/18 17:19:37 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;
	size_t	size;

	i = -1;
	size = ft_strlen(s);
	ptr = (char *)ft_malloc(size + 1);
	if (!ptr)
		return (NULL);
	while (++i < size)
		ptr[i] = s[i];
	ptr[i] = '\0';
	return (ptr);
}

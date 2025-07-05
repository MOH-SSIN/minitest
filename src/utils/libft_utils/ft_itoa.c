/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:17:32 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/05/18 17:19:22 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static size_t	count_size(long nbr)
{
	size_t	size;

	size = 0;
	if (nbr < 0)
	{
		nbr = nbr * (-1);
		size = 1;
	}
	if (nbr == 0)
		size = 1;
	else
	{
		while (nbr)
		{
			nbr = nbr / 10;
			size++;
		}
	}
	return (size);
}

char	*ft_itoa(int n)
{
	size_t	size;
	long	nbr;
	char	*str;
	int		negative;

	size = count_size((long)n);
	str = (char *)ft_malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	nbr = (long)n;
	negative = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		str[0] = '-';
		negative = 1;
	}
	str[size] = '\0';
	while (size > (size_t)negative)
	{
		str[size - 1] = nbr % 10 + '0';
		nbr = nbr / 10;
		size--;
	}
	return (str);
}

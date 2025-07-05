/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:51:01 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/05/22 13:19:58 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	add_fin_free(t_free **debut, t_free *new)
{
	t_free	*temp;

	if (!*debut)
	{
		*debut = new;
		return ;
	}
	temp = *debut;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_free	*add_new_free(void *rest)
{
	t_free	*new;

	new = malloc(sizeof(t_free));
	if (!new)
		return (NULL);
	new->add = rest;
	new->next = NULL;
	return (new);
}

void	*ft_malloc(size_t size)
{
	static t_free	*debut;
	t_free			*temp;
	void			*rest;

	rest = malloc(size);
	if (!rest)
		exit(0);
	temp = add_new_free(rest);
	if (!temp)
	{
		ft_free_all(debut);
		exit(0);
	}
	add_fin_free(&debut, temp);
	return (rest);
}

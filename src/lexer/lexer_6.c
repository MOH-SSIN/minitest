/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:00:39 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/05/14 18:14:39 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	singl_qoutes(t_token_node *debut)
{
	while (debut)
	{
		if (debut->type == SINGLE_Q)
			debut->value = ft_strtrim(debut->value, "\'");
		debut = debut->next;
	}
}

void	double_qoutes(t_token_node *debut)
{
	while (debut)
	{
		if (debut->type == DOUBLE_Q)
			debut->value = ft_strtrim(debut->value, "\"");
		debut = debut->next;
	}
}

void	suprime_qoutes(t_token_node *debut)
{
	singl_qoutes(debut);
	double_qoutes(debut);
}

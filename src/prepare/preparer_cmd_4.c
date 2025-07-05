/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparer_cmd_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:27:04 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/21 12:42:08 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	oui_space(char *str)
{
	while (*str)
	{
		if (!is_espace(*str))
			return (0);
		str++;
	}
	return (1);
}

t_token_node	*change_flag(t_token_node *debut)
{
	t_token_node	*temp;

	temp = debut;
	while (temp && temp->next)
	{
		if (temp->value && ft_fofo(temp->value, '=') && temp->flag == 0)
		{
			if (temp->next->flag == 1)
				temp->flag = 1;
		}
		temp = temp->next;
	}
	return (debut);
}

bool	is_assign_form(const char *value)
{
	int	i;

	i = 0;
	if (!value)
		return (false);
	while (value[i])
	{
		if (value[i] == '=')
			return (i > 0 && value[i + 1] == '\0');
		i++;
	}
	return (false);
}

bool	start_zone_has_equal(t_token_node *start)
{
	return (start && start->flag == 1 && is_assign_form(start->value));
}

int	ft_fofo(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

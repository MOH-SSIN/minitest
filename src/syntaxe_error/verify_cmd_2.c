/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_cmd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:03:39 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/05/25 11:53:21 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_error(bool print)
{
	if (print)
		write(2, "syntax error near unexpected token\n", 36);
	return (-1);
}

int	check_double_pipe_error(t_token_node *debut, bool print)
{
	t_token_node	*cur;

	cur = debut;
	while (cur)
	{
		if (cur->type == PIPE)
		{
			cur = cur->next;
			if (cur && cur->type == SPC)
				cur = cur->next;
			if (cur && cur->type == PIPE)
				return (print_error(print));
			if (!cur)
				return (print_error(print));
		}
		cur = cur->next;
	}
	return (0);
}

int	validate_pipe_position(t_token_node *debut, bool print)
{
	t_token_node	*cur;

	cur = debut;
	if (cur && cur->type == SPC)
		cur = cur->next;
	if (cur && cur->type == PIPE)
		return (print_error(print));
	return (0);
}

int	validate_redirections(t_token_node *debut, bool print)
{
	t_token_node	*cur;

	cur = debut;
	while (cur)
	{
		if (cur->type >= REDIRECT_IN && cur->type <= REDIRECT_OUT)
		{
			cur = cur->next;
			if (cur && cur->type == SPC)
				cur = cur->next;
			if (cur && cur->type != STRING && cur->type != SINGLE_Q
				&& cur->type != DOUBLE_Q && cur->type != VAR
				&& cur->type != DOUBLE_DLR && cur->type != EXIT_STATUS)
				return (print_error(print));
			if (!cur)
				return (print_error(print));
		}
		cur = cur->next;
	}
	return (0);
}

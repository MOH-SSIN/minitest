/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 08:26:55 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/05/15 12:05:27 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_red(int type)
{
	return (type == REDIRECT_APPEND || type == REDIRECT_IN
		|| type == REDIRECT_OUT || type == HEREDOC);
}

void	rm_red(t_token_node **debut, t_token_node **new_debut)
{
	t_token_node	*new_node;
	t_token_node	*cur;
	int				type;
	char			*value;
	int				heredoc_fd;

	type = (*debut)->type;
	heredoc_fd = (*debut)->fd_hrd;
	cur = (*debut)->next;
	while (cur && cur->type == SPC)
		cur = cur->next;
	if (cur)
	{
		value = cur->value;
		new_node = new_token(type, value, heredoc_fd);
		if (cur->flag)
			new_node->flag = true;
		add_lst_back_token(new_debut, new_node);
		(*debut) = cur->next;
	}
	else
		(*debut) = NULL;
}

t_token_node	*remove_red(t_token_node *debut)
{
	t_token_node	*new_debut;

	new_debut = NULL;
	while (debut)
	{
		if (is_red(debut->type))
			rm_red(&debut, &new_debut);
		else
		{
			add_lst_back_token(&new_debut, new_token(debut->type, debut->value,
					debut->fd_hrd));
			debut = debut->next;
		}
	}
	return (new_debut);
}

t_token_node	*remove_invalid_tokens(t_token_node *debut)
{
	t_token_node	*new_debut;
	t_token_node	*new_node;

	new_debut = NULL;
	while (debut)
	{
		if (debut->type == STRING && !debut->value)
		{
			debut = debut->next;
			continue ;
		}
		new_node = new_token(debut->type, debut->value, debut->fd_hrd);
		if (debut->flag)
			new_node->flag = true;
		add_lst_back_token(&new_debut, new_node);
		debut = debut->next;
	}
	return (new_debut);
}

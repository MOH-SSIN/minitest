/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparer_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:58:20 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/22 15:38:51 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*join_flag_tokens(t_token_node **cur)
{
	char	*joined;

	joined = NULL;
	while (*cur && (*cur)->flag == 1)
	{
		if ((*cur)->value && (*cur)->value[0] != '\0')
			joined = ft_strjoin(joined, (*cur)->value);
		*cur = (*cur)->next;
	}
	return (joined);
}

t_token_node	*fix_isolated_flagged_tokens(t_token_node *head)
{
	t_token_node	*prev;
	t_token_node	*cur;
	t_token_node	*next;
	bool			prev_ok;
	bool			next_ok;

	prev = NULL;
	cur = head;
	while (cur)
	{
		next = cur->next;
		if (cur->flag == 1)
		{
			prev_ok = (prev == NULL || prev->flag == 0);
			next_ok = (next == NULL || next->flag == 0);
			if (prev_ok && next_ok)
				cur->flag = 0;
		}
		prev = cur;
		cur = cur->next;
	}
	return (head);
}

t_cmd	*ft_split_cmd(t_token_node *debut_tmp)
{
	t_token_node	*new_red;
	t_token_node	*debut_red;
	char			**args;
	int				i;

	i = 0;
	debut_red = NULL;
	new_red = NULL;
	args = ft_malloc(sizeof(char *) * (ft_count_args_cmd(debut_tmp) + 1));
	if (!args)
		return (NULL);
	while (debut_tmp)
	{
		if (debut_tmp->type == STRING)
			args[i++] = ft_strdup(debut_tmp->value);
		if (is_red(debut_tmp->type))
			new_redirection(debut_tmp, &new_red, &debut_red);
		debut_tmp = debut_tmp->next;
	}
	args[i] = NULL;
	return (new_cmd(args, debut_red));
}

t_cmd	*token_list_to_cmd_list(t_token_node *debut)
{
	t_token_node	*debut_tmp;
	t_cmd			*new_cmd;
	t_token_node	*new_node;

	new_cmd = NULL;
	while (debut)
	{
		debut_tmp = NULL;
		while (debut)
		{
			if (debut->type == PIPE)
				break ;
			new_node = new_token(debut->type, debut->value, debut->fd_hrd);
			if (debut->flag)
				new_node->flag = true;
			add_lst_back_token(&debut_tmp, new_node);
			debut = debut->next;
		}
		add_lst_back_cmd(&new_cmd, ft_split_cmd(debut_tmp));
		if (debut)
			debut = debut->next;
	}
	return (new_cmd);
}

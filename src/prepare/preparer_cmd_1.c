/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparer_cmd_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 08:55:40 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/05/22 17:32:33 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*set_cmd_false_true(t_cmd **cmds)
{
	t_cmd	*cmd;

	if (!cmds || !*cmds)
		return (NULL);
	cmd = *cmds;
	cmd->isfirst = true;
	cmd->islast = false;
	if (cmd->next)
	{
		cmd = cmd->next;
		while (cmd->next)
		{
			cmd->isfirst = false;
			cmd->islast = false;
			cmd = cmd->next;
		}
		cmd->isfirst = false;
		cmd->islast = true;
	}
	else
		cmd->islast = true;
	return (*cmds);
}

int	ft_count_args_cmd(t_token_node *debut)
{
	int	nbr;

	nbr = 0;
	while (debut)
	{
		if (debut->type == STRING)
			nbr++;
		debut = debut->next;
	}
	return (nbr);
}

void	new_redirection(t_token_node *debut_tmp, t_token_node **new,
		t_token_node **debut_red)
{
	*new = new_token(debut_tmp->type, debut_tmp->value, debut_tmp->fd_hrd);
	if (debut_tmp->flag)
		(*new)->flag = true;
	add_lst_back_token(debut_red, *new);
}

t_cmd	*new_cmd(char **args, t_token_node *debut_red)
{
	t_cmd	*new_cmd;

	new_cmd = ft_malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->argv = args;
	new_cmd->red = debut_red;
	new_cmd->infile = dup(STDIN_FILENO);
	new_cmd->outfile = dup(STDOUT_FILENO);
	new_cmd->next = NULL;
	return (new_cmd);
}

void	add_lst_back_cmd(t_cmd **debut_cmd, t_cmd *new)
{
	t_cmd	*cur;

	cur = *debut_cmd;
	if (!cur)
	{
		*debut_cmd = new;
		return ;
	}
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

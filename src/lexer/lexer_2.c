/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:03:05 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/05/14 17:49:20 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*lstlast_token(t_token_node *cur)
{
	if (!cur)
		return (NULL);
	while (cur->next)
		cur = cur->next;
	return (cur->value);
}

void	add_lst_back_token(t_token_node **debut_token, t_token_node *new)
{
	t_token_node	*cur;

	cur = *debut_token;
	if (!cur)
	{
		*debut_token = new;
		return ;
	}
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

t_token_node	*new_token(int type_token, char *value, int fd)
{
	t_token_node	*new_tkn;

	new_tkn = (t_token_node *)ft_malloc(sizeof(t_token_node));
	new_tkn->type = type_token;
	new_tkn->value = value;
	new_tkn->flag = false;
	new_tkn->fd_hrd = fd;
	new_tkn->next = NULL;
	return (new_tkn);
}

t_token_node	*ft_tokenization(char *command, t_token_node **debut_token)
{
	int	i;
	int	len;

	len = ft_strlen(command);
	i = 0;
	while (command[i] && (command[i] == ' ' || (command[i] >= 9
				&& command[i] <= 13)))
		i++;
	while (i < len)
	{
		if (command[i] == '|')
			add_lst_back_token(debut_token, new_token(PIPE, "|", -2));
		else if (is_espace(command[i]))
			ft_espase(&i, command, debut_token);
		else if (is_quotes(command[i]))
			ft_single_double_qoutes(i, command, debut_token);
		else if (is_redirection(command[i]))
			ft_redirection(i, command, debut_token);
		else if ((command[i]) == '$')
			ft_dollar(&i, command, debut_token);
		else
			ft_string(i, command, debut_token);
		i += ft_strlen(lstlast_token(*debut_token));
	}
	return (*debut_token);
}

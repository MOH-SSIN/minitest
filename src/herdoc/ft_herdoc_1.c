/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 09:49:31 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/20 20:54:48 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	valide_delimiter(int type)
{
	return (type == STRING || type == SINGLE_Q || type == DOUBLE_Q
		|| type == VAR || type == DOUBLE_DLR || type == EXIT_STATUS);
}

char	*ft_delimiter(t_token_node **debut, int *flag)
{
	t_token_node	*cur;
	char			*delimiter;

	delimiter = NULL;
	cur = (*debut)->next;
	if (cur && cur->type == SPC)
		cur = cur->next;
	while (cur && valide_delimiter(cur->type))
	{
		if (!(*flag) && (cur->type == SINGLE_Q || cur->type == DOUBLE_Q))
			(*flag) = 42;
		if (!delimiter)
			delimiter = ft_strdup("");
		delimiter = ft_strjoin(delimiter, cur->value);
		cur = cur->next;
	}
	return (delimiter);
}

void	ft_herdoc(t_token_node *debut, t_env_var *env, t_minishell *data)
{
	int				flag;
	char			*delimiter;
	t_token_node	*cur;

	cur = NULL;
	flag = 0;
	while (debut)
	{
		if (debut->type == HEREDOC)
		{
			if (verify_cmd(cur, NULL, false) == -1)
				break ;
			delimiter = ft_delimiter(&debut, &flag);
			if (!delimiter)
				break ;
			debut->fd_hrd = readline_hdc(delimiter, env, flag, data);
			if (debut->fd_hrd == -3)
			{
				data->exit_status = 1;
				return ;
			}
		}
		add_lst_back_token(&cur, new_token(debut->type, debut->value, -3));
		debut = debut->next;
	}
}

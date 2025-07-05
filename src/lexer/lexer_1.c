/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:10:58 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/21 10:51:57 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	invalide_fd_hrdc(t_token_node *debut)
{
	t_token_node	*tmp;

	tmp = debut;
	while (tmp)
	{
		if (tmp->fd_hrd == -3)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_token_node	*gestion_input(char **command, t_token_node **debut_token,
		t_env_var *env, t_minishell *data)
{
	ft_handler_signal();
	rl_catch_signals = 0;
	*command = readline("minishell$ ");
	if (g_status == 1)
		data->exit_status = 1;
	if (!(*command))
	{
		write(1, "exit\n", 5);
		clean_cmd_line(*command);
		exit(data->exit_status);
	}
	if (*command[0])
		add_history(*command);
	*debut_token = ft_tokenization(*command, debut_token);
	if (validate_quotes(*command, false) == -1)
		return (*debut_token);
	suprime_qoutes(*debut_token);
	ft_herdoc(*debut_token, env, data);
	return (*debut_token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_cmd_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:33:44 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/09 13:53:32 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_exit(char *commande, t_minishell *data)
{
	(void)commande;
	data->exit_status = 258;
	unset_free(NULL, FREYI);
	close_fds_except_std();
}

void	clean_cmd_line(char *command)
{
	(void)command;
	unset_free(NULL, FREYI);
	close_fds_except_std();
}

int	quotes_error(char *command, int *i, char quote, bool print)
{
	while (command[*i] && command[*i] != quote)
		(*i)++;
	if (command[*i] == quote)
		return (0);
	if (print)
		write(2, "close quote\n", 12);
	return (-1);
}

int	validate_quotes(char *command, bool print)
{
	int		i;
	char	quote;

	i = 0;
	while (command && command[i])
	{
		if (command[i] == '\"' || command[i] == '\'')
		{
			quote = command[i];
			i++;
			if (quotes_error(command, &i, quote, print) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	verify_cmd(t_token_node *debut_token, char *command, bool print)
{
	if (validate_quotes(command, print) == -1)
		return (-1);
	if (validate_redirections(debut_token, print) == -1)
		return (-1);
	if (validate_pipe_position(debut_token, print) == -1)
		return (-1);
	if (check_double_pipe_error(debut_token, print) == -1)
	{
		if (!print)
			return (0);
		else
			return (-1);
	}
	return (0);
}

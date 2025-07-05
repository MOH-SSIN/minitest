/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:27:16 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/05/18 11:48:26 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_var(int i, char *command, t_token_node **debut_token)
{
	int		start;
	char	*str;

	start = i;
	str = NULL;
	i++;
	if (command[i] >= '0' && command[i] <= '9')
		str = ft_substr(command, start, (i + 1) - start);
	else
	{
		while (command[i] && (ft_isalnum(command[i]) || command[i] == '_'))
			i++;
		str = ft_substr(command, start, i - start);
	}
	add_lst_back_token(debut_token, new_token(VAR, str, -2));
}

void	ft_dollar(int *i, char *command, t_token_node **debut_token)
{
	if (command[*i] == '$' && command[*i + 1] == '?')
		add_lst_back_token(debut_token, new_token(EXIT_STATUS, "$?", -2));
	else if (command[*i] == '$' && command[*i + 1] == '$')
		add_lst_back_token(debut_token, new_token(DOUBLE_DLR, "$$", -2));
	else if ((command[*i] == '$' && command[*i + 1] == '\"')
		|| (command[*i] == '$' && command[*i + 1] == '\''))
	{
		add_lst_back_token(debut_token, new_token(STRING, "", -2));
		(*i)++;
	}
	else if (command[*i] == '$')
	{
		ft_var(*i, command, debut_token);
	}
}

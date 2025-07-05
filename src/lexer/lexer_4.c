/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:06:44 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/05/16 15:11:35 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_espase(int *i, char *commande, t_token_node **debut_token)
{
	add_lst_back_token(debut_token, new_token(SPC, " ", -2));
	while (commande[*i] && is_espace(commande[*i]))
		(*i)++;
	(*i)--;
}

int	is_quotes(char c)
{
	return (c == '\"' || c == '\'');
}

void	ft_single_qoutes(int i, char *command, t_token_node **debut_token)
{
	int		start;
	char	*str;

	start = i;
	i++;
	while (command[i])
	{
		if (command[i] == '\'')
			break ;
		i++;
	}
	str = ft_substr(command, start, (i + 1) - start);
	add_lst_back_token(debut_token, new_token(SINGLE_Q, str, -2));
}

void	ft_double_qoutes(int i, char *command, t_token_node **debut_token)
{
	int		start;
	char	*str;

	start = i;
	i++;
	while (command[i])
	{
		if (command[i] == '\"')
			break ;
		i++;
	}
	str = ft_substr(command, start, (i + 1) - start);
	add_lst_back_token(debut_token, new_token(DOUBLE_Q, str, -2));
}

void	ft_single_double_qoutes(int i, char *command,
		t_token_node **debut_token)
{
	if (command[i] == '\'')
		ft_single_qoutes(i, command, debut_token);
	else if (command[i] == '\"')
		ft_double_qoutes(i, command, debut_token);
}

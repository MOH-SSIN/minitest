/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:06:47 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/05/14 17:51:07 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_espace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_is_car_special(char c)
{
	return (c == '\"' || c == '\'' || c == '|' || c == '>' || c == '$'
		|| c == '<' || is_espace(c));
}

void	ft_string(int i, char *commande, t_token_node **debut_token)
{
	char	*str;
	int		start;

	start = i;
	while (commande[i] && !ft_is_car_special(commande[i]))
		i++;
	str = ft_substr(commande, start, i - start);
	add_lst_back_token(debut_token, new_token(STRING, str, -2));
}

int	is_redirection(char c)
{
	return (c == '>' || c == '<');
}

void	ft_redirection(int i, char *command, t_token_node **debut_token)
{
	if (command[i] == '>' && command[i + 1] == '>')
		add_lst_back_token(debut_token, new_token(REDIRECT_APPEND, ">>", -2));
	else if (command[i] == '<' && command[i + 1] == '<')
		add_lst_back_token(debut_token, new_token(HEREDOC, "<<", -2));
	else if (command[i] == '>')
		add_lst_back_token(debut_token, new_token(REDIRECT_OUT, ">", -2));
	else if (command[i] == '<')
		add_lst_back_token(debut_token, new_token(REDIRECT_IN, "<", -2));
}

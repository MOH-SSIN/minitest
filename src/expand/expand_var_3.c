/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:13:50 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/20 20:14:04 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	special_case_len(char *str)
{
	int	i;

	if (str[1] == '$' || str[1] == '?')
		return (2);
	if (ft_isdigit(str[1]))
		return (2);
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*decoupe_chaine_en_segment(char *str_var)
{
	int	i;

	i = 0;
	if (!str_var || str_var[0] == '\0')
		return (NULL);
	if (str_var[0] != '$')
	{
		while (str_var[i] && str_var[i] != '$')
			i++;
		return (ft_substr(str_var, 0, i));
	}
	i = special_case_len(str_var);
	return (ft_substr(str_var, 0, i));
}

char	*expand_vars_and_heredoc(char *cmd, t_env_var *env, t_minishell *data)
{
	char	*cmd_final;
	char	*str_var;
	char	*str_exp;
	int		i;

	i = 0;
	cmd_final = NULL;
	while (cmd[i])
	{
		str_var = decoupe_chaine_en_segment(cmd + i);
		if (str_var[0] != '$')
			str_exp = ft_strdup(str_var);
		else
			str_exp = expand_segment(str_var, env, data);
		if (!cmd_final)
			cmd_final = ft_strdup("");
		cmd_final = ft_strjoin(cmd_final, str_exp);
		i += ft_strlen(str_var);
	}
	return (cmd_final);
}

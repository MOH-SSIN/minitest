/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:26:11 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/25 16:11:44 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*expand_exit_status(int exit_status)
{
	return (ft_itoa(exit_status));
}

static char	*expand_dollar_var(char *str_var, int *i, t_env_var *env)
{
	int		count_dlr;
	char	*str_exp;

	count_dlr = *i;
	while (str_var[*i] && str_var[*i] == '$')
		(*i)++;
	count_dlr = *i - count_dlr;
	if (count_dlr % 2 == 0)
		str_exp = ft_strdup("$$");
	else
		str_exp = get_var_sigle_dolar(str_var + *i, env);
	return (str_exp);
}

char	*expand_segment(char *str_var, t_env_var *env, t_minishell *data)
{
	int		i;
	int		len;
	char	*str_exp;

	i = 0;
	str_exp = NULL;
	len = ft_strlen(str_var);
	while (i < len)
	{
		if (str_var[i] == '$' && str_var[i + 1] == '?')
			return (expand_exit_status(data->exit_status));
		if (str_var[i] == '$')
			return (expand_dollar_var(str_var, &i, env));
		i++;
	}
	return (str_exp);
}

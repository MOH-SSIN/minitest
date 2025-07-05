/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:16:52 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/05/18 11:47:47 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_var_depui_env(t_env_var *env, char *get_var)
{
	while (env)
	{
		if (ft_strcmp(env->cle, get_var) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*ft_get_var(char *str_var)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	if (ft_isdigit(str_var[i]))
		return (ft_substr(str_var, start, 1));
	while (str_var[i] && (str_var[i] == '_' || ft_isalnum(str_var[i])))
		i++;
	return (ft_substr(str_var, start, i));
}

char	*get_var_sigle_dolar(char *str_var, t_env_var *env)
{
	char	*get_var;
	char	*str_exp;

	get_var = NULL;
	str_exp = NULL;
	get_var = ft_get_var(str_var);
	if (get_var[0])
		str_exp = get_var_depui_env(env, get_var);
	else
		str_exp = ft_strdup("$");
	return (str_exp);
}

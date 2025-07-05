/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:50:12 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/02 18:00:50 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "PWD") == 0
		|| ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "ENV") == 0
		|| ft_strcmp(cmd, "ECHO") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	env_size(t_env_var *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**env_to_tab(t_env_var *env)
{
	char	**tab;
	int		i;
	int		size;
	char	*tmp;

	i = 0;
	size = env_size(env);
	tab = ft_malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	while (env)
	{
		if (env->value != NULL)
		{
			tmp = ft_strjoin(env->cle, "=");
			tab[i] = ft_strjoin(tmp, env->value);
			free(tmp);
		}
		else
			tab[i] = ft_strdup(env->cle);
		env = env->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	*get_env_value_char(t_env_var *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->cle, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_env_var	*get_env_value(t_env_var *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->cle, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:25:19 by idahhan           #+#    #+#             */
/*   Updated: 2025/05/25 11:31:20 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**env_to_tab_for_export(t_env_var *env)
{
	char	**tab;
	int		i;
	int		size;
	char	*tmp;

	(1) && (i = 0, size = env_size(env));
	tab = ft_malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	while (env)
	{
		if (env->env_flag == true)
		{
			if (env->value != NULL)
			{
				tmp = ft_strjoin(env->cle, "=");
				tab[i++] = ft_strjoin(tmp, env->value);
				free(tmp);
			}
			else
				tab[i++] = ft_strdup(env->cle);
		}
		env = env->next;
	}
	return (tab[i] = NULL, tab);
}

static void	print_export_line(char *entry)
{
	char	*eq;
	char	*key;
	char	*value;
	int		key_len;

	eq = ft_strchr(entry, '=');
	if (eq)
	{
		key_len = eq - entry;
		key = ft_substr(entry, 0, key_len);
		value = ft_substr(eq + 1, 0, ft_strlen(eq + 1));
		printf("declare -x %s=\"%s\"\n", key, value);
		free(key);
		free(value);
	}
	else
		printf("declare -x %s\n", entry);
}

void	print_sorted_env(t_env_var *env)
{
	char	**tab;
	int		i;

	tab = env_to_tab_for_export(env);
	sort_env_tab(tab);
	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "_=", 2) == 0)
		{
			free(tab[i++]);
			continue ;
		}
		print_export_line(tab[i]);
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	set_env_value(t_env_var **env, char *key, char *value)
{
	t_env_var	*tmp;
	t_env_var	*new_var;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->cle, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new_var = add_new_env(key, value, true);
	add_lst_back_env(env, new_var);
}

bool	is_append_export(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && !(arg[i] == '+' && arg[i + 1] == '='))
		i++;
	return (arg[i] == '+' && arg[i + 1] == '=');
}

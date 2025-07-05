/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:56:02 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/09 15:57:23 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env_var	*add_new_env(char *key, char *value, bool env_flag)
{
	t_env_var	*new;

	new = malloc(sizeof(t_env_var));
	if (!new)
		return (NULL);
	new->cle = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	new->env_flag = env_flag;
	return (new);
}

void	add_lst_back_env(t_env_var **lst, t_env_var *new_node)
{
	t_env_var	*last;

	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

void	init_unset_env(t_env_var **debut_env)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	add_lst_back_env(debut_env, add_new_env("PWD", cwd, true));
	add_lst_back_env(debut_env, add_new_env("SHLVL", "0", true));
	add_lst_back_env(debut_env, add_new_env("_", "/usr/bin/env", true));
	add_lst_back_env(debut_env, add_new_env("PATH",
			"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", false));
	add_lst_back_env(debut_env, add_new_env("OLDPWD", NULL, true));
}

void	help_func(t_env_var **debut_env, t_minishell *data)
{
	char	*unset_oldpwd[3];
	char	*export_oldpwd[3];

	unset_oldpwd[0] = "unset";
	unset_oldpwd[1] = "OLDPWD";
	unset_oldpwd[2] = NULL;
	export_oldpwd[0] = "export";
	export_oldpwd[1] = "OLDPWD";
	export_oldpwd[2] = NULL;
	exec_unset(debut_env, unset_oldpwd, data);
	exec_export(export_oldpwd, *debut_env, data);
}

void	init_env(t_env_var **debut_env, char **env, t_minishell *data)
{
	int		i;
	int		j;
	char	*cle;
	char	*value;

	i = -1;
	if (!env || !env[0])
	{
		init_unset_env(debut_env);
		return ;
	}
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		cle = ft_substr(env[i], 0, j);
		value = ft_substr(env[i], j + 1, (ft_strlen(env[i]) - (j + 1)));
		add_lst_back_env(debut_env, add_new_env(cle, value, true));
		free(cle);
		free(value);
	}
	help_func(debut_env, data);
}

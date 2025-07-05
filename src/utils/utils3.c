/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:52:03 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/25 12:17:50 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_or_add_env_value(t_env_var **env, char *key, char *value,
		bool env_flag)
{
	t_env_var	*curr;
	char		*safe_value;

	curr = *env;
	while (curr)
	{
		if (strcmp(curr->cle, key) == 0)
		{
			curr->value = ft_strdup(value);
			return ;
		}
		curr = curr->next;
	}
	if (value)
		safe_value = value;
	else
		safe_value = ft_strdup("");
	add_lst_back_env(env, add_new_env(key, safe_value, env_flag));
}

char	*join_path(const char *base, const char *relative)
{
	char	*result;
	size_t	len_base;
	size_t	len_rel;
	int		add_slash;

	if (!base || !relative)
		return (NULL);
	if (!base || ft_strlen(base) == 0)
		return (ft_strdup(relative));
	len_base = ft_strlen(base);
	len_rel = ft_strlen(relative);
	add_slash = 0;
	if (len_rel == 0)
		return (ft_strdup(base));
	if (base[len_base - 1] != '/')
		add_slash = 1;
	result = ft_malloc(len_base + len_rel + add_slash + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, base);
	if (add_slash)
		ft_strcat(result, "/");
	ft_strcat(result, relative);
	return (result);
}

int	get_logical_pwd(char *buffer, t_env_var *envp)
{
	char	*pwd;

	pwd = get_env_value_char(envp, "PWD");
	if (!pwd)
		return (0);
	ft_strlcpy(buffer, pwd, PATH_MAX);
	return (1);
}

int	get_physical_pwd(char *buffer)
{
	if (!getcwd(buffer, PATH_MAX))
		return (0);
	return (1);
}

int	fail_redirection(t_cmd *cmd)
{
	close(cmd->infile);
	close(cmd->outfile);
	return (0);
}

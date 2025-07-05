/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:50:39 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/22 16:41:20 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_path_directories(char **env)
{
	size_t	len;
	int		i;
	char	*path_env;

	len = ft_strlen("PATH");
	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], len) == 0 && env[i][len] == '=')
		{
			path_env = env[i] + len + 1;
			return (ft_split(path_env, ':'));
		}
		i++;
	}
	return (NULL);
}

char	*get_full_path_from_paths(char *command, char **paths)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

static char	*search_in_path(const char *command, char **env)
{
	char	**paths;
	char	*full_path;

	paths = get_path_directories(env);
	if (!paths)
		return (NULL);
	full_path = get_full_path_from_paths((char *)command, paths);
	ft_free_split(paths);
	return (full_path);
}

static char	*lookup_in_path(const char *command, char **env, t_minishell *data)
{
	struct stat	st;
	char		*full_path;

	full_path = search_in_path(command, env);
	if (full_path)
		return (full_path);
	if (access(command, F_OK) == 0)
	{
		if (stat(command, &st) == 0 && S_ISDIR(st.st_mode))
		{
			error_command_not_found(command, data);
			return (NULL);
		}
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		else
		{
			error_permission_denied(command, data);
			return (NULL);
		}
	}
	return (NULL);
}

char	*find_command_path(const char *command, char **env, t_minishell *data)
{
	struct stat	st;
	size_t		len;

	if (ft_strchr(command, '/') || (command[0] == '.' && command[1] == '/'))
	{
		len = ft_strlen(command);
		if (ft_strchr(command, '/') || (command[0] == '.' && command[1] == '/'))
		{
			if (len > 0 && command[len - 1] == '/')
				error_is_directory(command);
			if (access(command, F_OK) == -1)
				error_no_such_file(command, data);
			if (stat(command, &st) == 0 && S_ISDIR(st.st_mode))
				error_is_directory(command);
			if (access(command, X_OK) == -1)
				error_permission_denied(command, data);
		}
		return (ft_strdup(command));
	}
	return (lookup_in_path(command, env, data));
}

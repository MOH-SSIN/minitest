/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:02:56 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/22 16:42:23 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	error_path_missing(const char *argv, t_minishell *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	data->exit_status = 127;
}

static void	err_cmd_not_found(const char *argv, t_minishell *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": command not found\n", 2);
	data->exit_status = 127;
}

void	exec_env(char *argv, t_env_var *env, t_minishell *data)
{
	char	**envp;
	char	*path_value;

	envp = env_to_tab(env);
	path_value = get_env_value_char(env, "PATH");
	if (!path_value)
	{
		error_path_missing(argv, data);
		return ;
	}
	else if (find_command_path(argv, envp, data) == NULL)
	{
		err_cmd_not_found(argv, data);
		return ;
	}
	while (env)
	{
		if (ft_strcmp(env->cle, "_") == 0)
			env->value = find_command_path(argv, envp, data);
		if (env->value && env->env_flag == true)
			printf("%s=%s\n", env->cle, env->value);
		env = env->next;
	}
	data->exit_status = 0;
}

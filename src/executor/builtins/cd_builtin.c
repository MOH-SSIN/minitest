/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:18:19 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/09 15:49:14 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*get_target_directory(char **argv, t_minishell *data)
{
	char	*home;

	if (!argv[1])
	{
		home = get_env_value_char(data->envp, "HOME");
		if (!home)
		{
			printf("minishell: cd: HOME not set\n");
			data->exit_status = 1;
			return (NULL);
		}
		return (home);
	}
	return (argv[1]);
}

static void	set_oldpwd(char *oldpwd, t_env_var *envp)
{
	if (!get_physical_pwd(oldpwd))
	{
		if (!get_logical_pwd(oldpwd, envp))
			ft_strlcpy(oldpwd, "", PATH_MAX);
	}
}

static void	update_cd_env(t_env_var *envp, t_pwd_data *pwd_data)
{
	if (pwd_data->pwd_before)
	{
		if (!pwd_data->oldpwd_before)
			update_or_add_env_value(&envp, "OLDPWD", pwd_data->oldpwd, false);
		else
			update_or_add_env_value(&envp, "OLDPWD", pwd_data->oldpwd, true);
		update_or_add_env_value(&envp, "PWD", pwd_data->newpwd, true);
	}
	else
	{
		if (pwd_data->oldpwd_before)
			update_or_add_env_value(&envp, "OLDPWD", "", true);
		else if (!pwd_data->oldpwd_before)
			;
		update_or_add_env_value(&envp, "PWD", pwd_data->newpwd, false);
	}
}

static void	update_pwd_logically(t_minishell *data, char *target_dir,
		t_pwd_data *pwd_data)
{
	char	*logical_newpwd;

	error_open_dir();
	logical_newpwd = join_path(data->logical_pwd, target_dir);
	if (logical_newpwd)
	{
		ft_strlcpy(pwd_data->newpwd, logical_newpwd, PATH_MAX);
		update_cd_env(data->envp, pwd_data);
		ft_strlcpy(data->logical_pwd, logical_newpwd, PATH_MAX);
		free(logical_newpwd);
	}
	else
	{
		ft_strlcpy(pwd_data->newpwd, target_dir, PATH_MAX);
		update_cd_env(data->envp, pwd_data);
	}
}

void	exec_cd(char **argv, t_minishell *data)
{
	t_pwd_data	pwd_data;
	char		*target_dir;

	pwd_data.pwd_before = get_env_value_char(data->envp, "PWD");
	pwd_data.oldpwd_before = get_env_value_char(data->envp, "OLDPWD");
	target_dir = get_target_directory(argv, data);
	if (!target_dir)
		return ;
	set_oldpwd(pwd_data.oldpwd, data->envp);
	if (chdir(target_dir) != 0)
	{
		handle_cd_error(target_dir, data);
		return ;
	}
	if (!get_physical_pwd(pwd_data.newpwd))
		update_pwd_logically(data, target_dir, &pwd_data);
	else
	{
		update_cd_env(data->envp, &pwd_data);
		ft_strlcpy(data->logical_pwd, pwd_data.newpwd, PATH_MAX);
	}
	data->exit_status = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:18:28 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/09 16:13:29 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	exec_pwd(t_minishell *data)
{
	char	cwd[PATH_MAX];
	char	*logical_pwd;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		logical_pwd = data->logical_pwd;
		if (logical_pwd)
			printf("%s\n", logical_pwd);
		else
			ft_putstr_fd("pwd: No such file or directory\n", 2);
	}
	data->exit_status = 0;
}

void	exec_builtin(t_cmd *cmd, t_minishell *data)
{
	if (!(ft_strcmp(cmd->argv[0], "echo")) || !(ft_strcmp(cmd->argv[0],
				"ECHO")))
		exec_echo(cmd->argv, data);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		exec_cd(cmd->argv, data);
	else if (!(ft_strcmp(cmd->argv[0], "pwd")) || !(ft_strcmp(cmd->argv[0],
				"PWD")))
		exec_pwd(data);
	else if (!(ft_strcmp(cmd->argv[0], "env")) || !(ft_strcmp(cmd->argv[0],
				"ENV")))
		exec_env(cmd->argv[0], data->envp, data);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		exec_export(cmd->argv, data->envp, data);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		exec_unset(&data->envp, cmd->argv, data);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		exec_exit(&cmd->argv[0], true, data);
}

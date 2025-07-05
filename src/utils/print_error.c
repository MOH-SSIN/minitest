/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:53:43 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/22 16:40:19 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_command_not_found(const char *cmd, t_minishell *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	data->exit_status = 127;
	exit(data->exit_status);
}

void	error_permission_denied(const char *cmd, t_minishell *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	data->exit_status = 126;
	exit(data->exit_status);
}

void	error_no_such_file(const char *cmd, t_minishell *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	data->exit_status = 127;
	exit(data->exit_status);
}

void	error_is_directory(const char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": is a directory\n", 2);
	exit(126);
}

void	error_open_file(const char *filename, t_minishell *data)
{
	ft_putstr_fd("minishell: ", 2);
	perror(filename);
	data->exit_status = 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:16:38 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/21 17:00:32 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_fork(t_minishell *data)
{
	perror("minishell: fork");
	data->exit_status = 1;
	exit(data->exit_status);
}

static void	wait_for_child(pid_t pid, t_minishell *data)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit: 3\n", 8);
		data->exit_status = 128 + WTERMSIG(status);
	}
}

void	handle_empty_executor(char *path, char **envp)
{
	char	*sh_argv[3];

	if (errno == ENOEXEC)
	{
		sh_argv[0] = "/bin/sh";
		sh_argv[1] = path;
		sh_argv[2] = NULL;
		execve("/bin/sh", sh_argv, envp);
	}
}

void	handle_children(t_cmd *cmd, char **envp, t_minishell *data)
{
	struct stat	st;
	char		*path;

	if (!cmd->argv[0] || cmd->argv[0][0] == '\0')
		error_command_not_found(cmd->argv[0], data);
	path = find_command_path(cmd->argv[0], envp, data);
	if (!path)
		error_command_not_found(cmd->argv[0], data);
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		if (cmd->argv[0][0] != '/' && !(cmd->argv[0][0] == '.'
				&& cmd->argv[0][1] == '/') && !ft_strchr(cmd->argv[0], '/'))
			error_command_not_found(cmd->argv[0], data);
		else
			error_is_directory(cmd->argv[0]);
	}
	execve(path, cmd->argv, envp);
	handle_empty_executor(path, envp);
	exit(127);
}

void	exec_external(t_cmd *cmd, t_minishell *data)
{
	pid_t			pid;
	char			**envp;
	struct termios	saved_termios;

	tcgetattr(STDIN_FILENO, &saved_termios);
	ignore_sig();
	(1) && (envp = env_to_tab(data->envp), pid = fork());
	if (pid < 0)
		error_fork(data);
	if (pid == 0)
	{
		restore_sig();
		if (set_redirection(cmd, data) == -1)
			exit(data->exit_status);
		handle_children(cmd, envp, data);
	}
	else
	{
		wait_for_child(pid, data);
		tcsetattr(STDIN_FILENO, TCSANOW, &saved_termios);
	}
}

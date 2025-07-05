/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:17:40 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/25 12:02:03 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	close_unused_fds(t_cmd *cmd, int prev_fd)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->pipe_fd[0] > 2)
		close(cmd->pipe_fd[0]);
	if (cmd->pipe_fd[1] > 2)
		close(cmd->pipe_fd[1]);
}

static void	wait_for_children(pid_t last_pid, t_minishell *data)
{
	int	status;

	if (waitpid(last_pid, &status, 0) == -1)
		perror("waitpid");
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_status = 128 + WTERMSIG(status);
	while (wait(NULL) > 0)
		;
}

static void	handle_child(t_cmd *cmd, int prev_fd, t_minishell *data,
		char **envp)
{
	restore_sig();
	if (!cmd->isfirst)
		dup2(prev_fd, STDIN_FILENO);
	if (!cmd->islast)
	{
		close(cmd->pipe_fd[0]);
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	}
	close_unused_fds(cmd, prev_fd);
	if (set_redirection(cmd, data) == -1)
		exit(data->exit_status);
	if (is_builtin(cmd->argv[0]))
	{
		exec_builtin(cmd, data);
		exit(data->exit_status);
	}
	handle_children(cmd, envp, data);
}

static pid_t	handle_fork_and_exec(t_cmd *cmd, int *prev_fd,
		t_minishell *data, char **envp)
{
	pid_t	pid;

	ignore_sig();
	pid = fork();
	if (pid == 0)
		handle_child(cmd, *prev_fd, data, envp);
	else if (pid < 0)
		error_fork(data);
	return (pid);
}

void	execute_pipeline(t_cmd *cmd, t_minishell *data)
{
	int		prev_fd;
	char	**envp;
	pid_t	last_pid;
	pid_t	current_pid;

	(1) && (envp = env_to_tab(data->envp), prev_fd = -1, last_pid = -1);
	while (cmd)
	{
		if (!cmd->islast && pipe(cmd->pipe_fd) == -1)
			return ((perror("pipe")), exit(1));
		current_pid = handle_fork_and_exec(cmd, &prev_fd, data, envp);
		if (cmd->islast)
			last_pid = current_pid;
		if (!cmd->isfirst)
			close(prev_fd);
		if (!cmd->islast)
		{
			close(cmd->pipe_fd[1]);
			prev_fd = cmd->pipe_fd[0];
		}
		else
			prev_fd = -1;
		cmd = cmd->next;
	}
	wait_for_children(last_pid, data);
}

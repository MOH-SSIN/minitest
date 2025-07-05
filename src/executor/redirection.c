/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:17:45 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/25 19:19:28 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	red_in(t_token_node *red, t_minishell *data)
{
	int	fd;

	if (red->flag || !red->value)
	{
		write(2, "minishell: ambiguous redirect\n", 30);
		data->exit_status = 1;
		return (-1);
	}
	fd = open(red->value, O_RDONLY);
	if (fd < 0)
		return (error_open_file(red->value, data), -1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	red_out(t_token_node *red, t_minishell *data)
{
	int	fd;

	if (red->flag || !red->value)
	{
		write(2, "minishell: ambiguous redirect\n", 30);
		data->exit_status = 1;
		return (-1);
	}
	fd = open(red->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (error_open_file(red->value, data), -1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	red_append(t_token_node *red, t_minishell *data)
{
	int	fd;

	if (red->flag || !red->value)
	{
		write(2, "minishell: ambiguous redirect\n", 30);
		data->exit_status = 1;
		return (-1);
	}
	fd = open(red->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (error_open_file(red->value, data), -1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	heredoc(t_token_node *red, t_minishell *data)
{
	int	fd;

	fd = red->fd_hrd;
	if (fd < 0)
		return (error_open_file(red->value, data), -1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	set_redirection(t_cmd *cmd, t_minishell *data)
{
	t_token_node	*red;

	red = cmd->red;
	while (red)
	{
		if ((red->type == REDIRECT_IN) && (red_in(red, data) == -1))
			return (-1);
		else if ((red->type == REDIRECT_OUT) && (red_out(red, data) == -1))
			return (-1);
		else if ((red->type == REDIRECT_APPEND)
			&& (red_append(red, data) == -1))
			return (-1);
		else if ((red->type == HEREDOC) && (heredoc(red, data) == -1))
			return (-1);
		red = red->next;
	}
	return (0);
}

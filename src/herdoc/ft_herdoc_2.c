/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:10:46 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/21 09:46:26 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	write_to_file(char *buffer)
{
	char	*file_tmp;
	int		i;
	int		fd;
	int		fd_read;

	file_tmp = ft_strdup("hiba.txt");
	i = 0;
	while (access(file_tmp, F_OK) != -1)
		file_tmp = ft_strjoin("hiba.txt", ft_itoa(i++));
	fd = open(file_tmp, O_CREAT | O_RDWR, 0777);
	fd_read = open(file_tmp, O_RDWR, 0777);
	if (fd < 0)
		write(2, "Error\n", 6);
	if (fd_read < 0)
		write(2, "Error\n", 6);
	if (!buffer)
		buffer = ft_strdup("");
	write(fd, buffer, ft_strlen(buffer));
	close(fd);
	unlink(file_tmp);
	return (fd_read);
}

char	*add_cmd_dn_buffer(char *cmd, char *buffer)
{
	if (!cmd)
		cmd = ft_strdup("");
	if (!buffer)
		buffer = ft_strdup("");
	buffer = ft_strjoin(buffer, cmd);
	buffer = ft_strjoin(buffer, ft_strdup("\n"));
	return (buffer);
}

int	readline_hdc(char *delimiter, t_env_var *env, int flag, t_minishell *data)
{
	char	*cmd;
	char	*cmd_copy;
	char	*buffer;

	buffer = NULL;
	signal(SIGINT, handel_herdoc);
	while (1)
	{
		cmd = readline("> ");
		cmd_copy = cmd;
		if (!ttyname(0))
			return (free(cmd_copy), open(ttyname(2), O_RDWR), -3);
		if (!cmd)
			return (write_to_file(buffer));
		if (!ft_strcmp(cmd, delimiter))
		{
			free(cmd_copy);
			break ;
		}
		if (flag != 42)
			cmd = expand_vars_and_heredoc(cmd, env, data);
		buffer = add_cmd_dn_buffer(cmd, buffer);
		free(cmd_copy);
	}
	return (write_to_file(buffer));
}

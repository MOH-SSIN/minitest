/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:50:30 by idahhan           #+#    #+#             */
/*   Updated: 2025/05/23 12:59:35 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_cmd_list(t_cmd **cmd_list)
{
	t_cmd	*tmp;
	int		i;

	if (!cmd_list || !*cmd_list)
		return ;
	while (*cmd_list)
	{
		tmp = (*cmd_list)->next;
		if ((*cmd_list)->argv)
		{
			i = 0;
			while ((*cmd_list)->argv[i])
			{
				free((*cmd_list)->argv[i]);
				i++;
			}
			free((*cmd_list)->argv);
		}
		free(*cmd_list);
		*cmd_list = tmp;
	}
}

void	free_env(t_env_var *env)
{
	t_env_var	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->cle);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	close_fds_except_std(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	ft_free_all(t_free *debut)
{
	t_free	*temp;
	t_free	*next;

	temp = debut;
	while (temp)
	{
		next = temp->next;
		free(temp->add);
		free(temp);
		temp = next;
	}
	debut = NULL;
}

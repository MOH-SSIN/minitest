/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:29:38 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/09 15:48:46 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_varname(const char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0])
		return (false);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (false);
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (true);
		if (arg[i] == '=')
			return (true);
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	sort_env_tab(char **tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[j + 1])
		{
			if (ft_strcmp(tab[j], tab[j + 1]) > 0)
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	check_exit_status(int has_error, t_minishell *data)
{
	if (has_error)
		data->exit_status = 1;
	else
		data->exit_status = 0;
}

void	error_open_dir(void)
{
	ft_putstr_fd("cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	perror("");
}

void	handle_cd_error(char *target_dir, t_minishell *data)
{
	printf("minishell: cd: %s: %s\n", target_dir, strerror(errno));
	data->exit_status = 1;
}

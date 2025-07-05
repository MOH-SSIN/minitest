/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:19:50 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/21 15:08:10 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static bool	check_varname_unset(const char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0])
		return (false);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (false);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	unset_free(t_env_var *current, int status)
{
	static t_free	*debut_free = NULL;
	t_free			*temp;
	t_free			*check;

	if (status == AJOUTER && current != NULL)
	{
		check = debut_free;
		while (check)
		{
			if (check->add == current)
				return ;
			check = check->next;
		}
		temp = add_new_free(current);
		if (temp)
			add_fin_free(&debut_free, temp);
	}
	else if (status == FREYI)
	{
		ft_free_all(debut_free);
		debut_free = NULL;
	}
}

void	unset_var(t_env_var **env, const char *var)
{
	t_env_var	*current;
	t_env_var	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->cle, var) == 0)
		{
			if (!ft_strcmp(current->cle, "_"))
				return ;
			if (prev == NULL)
				*env = current->next;
			else
				prev->next = current->next;
			unset_free(current, AJOUTER);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	exec_unset(t_env_var **env, char **argv, t_minishell *data)
{
	int	i;
	int	has_error;

	i = 1;
	has_error = 0;
	while (argv[i])
	{
		if (!check_varname_unset(argv[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", argv[i]);
			has_error = 1;
		}
		else
			unset_var(env, argv[i]);
		i++;
	}
	check_exit_status(has_error, data);
}

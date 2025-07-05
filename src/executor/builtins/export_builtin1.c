/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:18:38 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/22 10:38:54 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	handle_append_expand(char *cmd, char *key, char *value,
		t_env_var *envp)
{
	t_env_var	*var;
	char		*new_value;
	int			key_len;

	key_len = ft_strchr(cmd, '+') - cmd;
	key = ft_substr(cmd, 0, key_len);
	value = ft_substr(cmd, key_len + 2, ft_strlen(cmd) - key_len - 2);
	var = get_env_value(envp, key);
	if (var)
	{
		new_value = ft_strjoin(var->value, value);
		set_env_value(&envp, key, new_value);
		free(new_value);
	}
	else
		set_env_value(&envp, key, value);
	free(key);
	free(value);
}

static void	handle_export_with_value(const char *cmd, char *key, char *value,
		t_env_var *envp)
{
	int	equal_sign;

	equal_sign = ft_strchr(cmd, '=') - cmd;
	key = ft_substr(cmd, 0, equal_sign);
	value = ft_substr(cmd, equal_sign + 1, ft_strlen(cmd) - (equal_sign - 1));
	set_env_value(&envp, key, value);
	free(key);
	free(value);
}

void	handle_empty_value(char *cmd, t_env_var *envp)
{
	t_env_var	*var;

	if (!get_env_value(envp, cmd))
	{
		var = add_new_env(cmd, NULL, true);
		add_lst_back_env(&envp, var);
	}
}

void	handle_export(char *cmd, char *key, char *value, t_env_var *envp)
{
	char	*equal;

	equal = ft_strchr(cmd, '=');
	if (equal && (equal == cmd || *(equal - 1) != '+'))
		handle_export_with_value(cmd, key, value, envp);
	else if (is_append_export(cmd))
		handle_append_expand(cmd, key, value, envp);
	else
		handle_empty_value(cmd, envp);
}

void	exec_export(char **argv, t_env_var *envp, t_minishell *data)
{
	int		i;
	char	*key;
	char	*value;
	int		has_error;

	(1) && (key = NULL, value = NULL, i = 0, has_error = 0);
	if (!argv[1])
	{
		print_sorted_env(envp);
		return ;
	}
	while (argv[++i])
	{
		if (!check_varname(argv[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				argv[i]);
			has_error = 1;
			continue ;
		}
		else
			handle_export(argv[i], key, value, envp);
	}
	check_exit_status(has_error, data);
}

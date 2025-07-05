/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 01:23:06 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/25 17:46:15 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int			g_status = 0;

t_cmd	*ft_prepare_cmd(t_token_node *debut_token, t_env_var *debut_env,
		t_minishell *data)
{
	t_token_node	*debut;
	t_cmd			*cmd_final;

	debut = expand_var(debut_token, debut_env, data);
	debut = change_flag(debut);
	debut = regrouper_tokens_marques(debut);
	debut = ft_concate_tkn(debut);
	debut = fix_isolated_flagged_tokens(debut);
	debut = remove_red(debut);
	debut = remove_invalid_tokens(debut);
	cmd_final = token_list_to_cmd_list(debut);
	return (cmd_final);
}

void	handle_input(t_env_var *debut_env, t_minishell *data)
{
	char			*command;
	t_token_node	*debut_token;
	t_cmd			*cmd_final;

	(1) && (command = NULL, cmd_final = NULL);
	while (1 && isatty(STDIN_FILENO))
	{
		debut_env = data->envp;
		debut_token = NULL;
		gestion_input(&command, &debut_token, debut_env, data);
		if (invalide_fd_hrdc(debut_token) == 1)
			clean_cmd_line(command);
		else if (verify_cmd(debut_token, command, true) == -1)
			clean_exit(command, data);
		else
		{
			cmd_final = ft_prepare_cmd(debut_token, debut_env, data);
			data->cmd_list = set_cmd_false_true(&cmd_final);
			execute_cmds(data);
			clean_cmd_line(command);
		}
		if (command)
			free(command);
		g_status = 0;
	}
}

t_env_var	*find_env(t_env_var *env, const char *name)
{
	while (env)
	{
		if (ft_strcmp(env->cle, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	handle_shlvl(t_env_var **env)
{
	t_env_var	*node;
	int			lvl;

	node = find_env(*env, "SHLVL");
	if (node && node->value)
	{
		lvl = ft_atol(node->value);
		if (lvl < 0)
			node->value = ft_itoa(0);
		else if (lvl == 999)
		{
			node->value = ft_strdup("");
			lvl = 0;
		}
		else if (lvl >= 1000)
			node->value = ft_itoa(1);
		else
		{
			lvl++;
			node->value = ft_itoa(lvl);
		}
	}
	else
		add_new_env("SHLVL", "1", true);
}

int	main(int argc, char **argv, char **env)
{
	t_env_var	*debut_env;
	t_minishell	data;
	char		*pwd_env;

	(void)argc;
	(void)argv;
	debut_env = NULL;
	init_env(&debut_env, env, &data);
	data.envp = debut_env;
	data.exit_status = 0;
	handle_shlvl(&data.envp);
	pwd_env = get_env_value_char(data.envp, "PWD");
	if (pwd_env)
		ft_strlcpy(data.logical_pwd, pwd_env, PATH_MAX);
	else if (getcwd(data.logical_pwd, PATH_MAX))
		;
	else
		ft_strlcpy(data.logical_pwd, "", PATH_MAX);
	close_fds_except_std();
	handle_input(debut_env, &data);
	free_env(debut_env);
	return (0);
}

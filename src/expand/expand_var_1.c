/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:02:18 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/25 16:12:36 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_expand_var(t_token_node *debut, t_env_var *env, t_minishell *data)
{
	char	*str_var;
	char	*str_exp;

	str_var = debut->value;
	if (ft_strlen(str_var) == 1)
		debut->value = ft_strdup("$");
	else
	{
		str_exp = expand_segment(str_var, env, data);
		debut->value = str_exp;
	}
}

void	add_mots_to_new_list(t_token_node **new_debut, char **mots)
{
	t_token_node	*tmp;
	t_token_node	*new;
	int				i;
	int				is_hrd;

	is_hrd = search_hrd(*new_debut);
	i = 0;
	tmp = NULL;
	while (mots && mots[i])
	{
		if (!is_espace(mots[i][0]))
			new = new_token(VAR, mots[i], -2);
		else if (is_espace(mots[i][0]) && is_hrd == 1)
			new = new_token(STRING, mots[i], -2);
		else if (is_espace(mots[i][0]))
			new = new_token(SPC, mots[i], -2);
		new->flag = 4;
		add_lst_back_token(new_debut, new);
		if (!tmp)
			tmp = new;
		i++;
	}
	if (tmp && i > 1)
		tmp->flag = true;
}

void	expand_typ_var(t_token_node **new_debut, t_token_node *debut,
		t_env_var *env, t_minishell *data)
{
	char			**mots;
	t_token_node	*new;

	ft_expand_var(debut, env, data);
	mots = split_words_and_spaces(debut->value);
	if (!mots || !mots[0])
	{
		new = new_token(VAR, NULL, debut->fd_hrd);
		new->flag = true;
		add_lst_back_token(new_debut, new);
	}
	add_mots_to_new_list(new_debut, mots);
}

t_token_node	*expand_var(t_token_node *debut, t_env_var *env,
		t_minishell *data)
{
	t_token_node	*new_debut;

	new_debut = NULL;
	while (debut)
	{
		if (debut->type == EXIT_STATUS)
		{
			debut->value = ft_itoa(data->exit_status);
			add_lst_back_token(&new_debut, new_token(STRING, debut->value,
					debut->fd_hrd));
		}
		else if (debut->type == VAR)
			expand_typ_var(&new_debut, debut, env, data);
		else if (debut->type == DOUBLE_Q && debut->value[0])
			add_lst_back_token(&new_debut, new_token(debut->type,
					expand_vars_and_heredoc(debut->value, env, data),
					debut->fd_hrd));
		else
			add_lst_back_token(&new_debut, new_token(debut->type, debut->value,
					debut->fd_hrd));
		debut = debut->next;
	}
	return (new_debut);
}

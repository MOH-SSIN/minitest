/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:18:33 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/09 15:41:09 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	get_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	validate_number(const char *str, int i, unsigned long long limit)
{
	unsigned long long	num;

	num = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (num > (limit - (str[i] - '0')) / 10)
			return (0);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}

static int	is_valid_long(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	num;
	unsigned long long	limit;

	(1) && (num = 0, sign = 1, i = 0);
	if (!str || !str[0])
		return (0);
	sign = get_sign(str, &i);
	if (!str[i])
		return (0);
	if (sign == 1)
		limit = (unsigned long long)LONG_MAX;
	else
		limit = (unsigned long long)LONG_MAX + 1;
	return (validate_number(str, i, limit));
}

static void	error_exit_chararg(const char *cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

void	exec_exit(char **argv, bool is_forked, t_minishell *data)
{
	long	exit_code;

	if (!is_forked)
		write(2, "exit\n", 5);
	if (!argv[1])
		exit(data->exit_status);
	if (!is_valid_long(argv[1]))
		error_exit_chararg(argv[1]);
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->exit_status = 1;
		return ;
	}
	exit_code = ft_atol(argv[1]);
	exit(exit_code % 256);
}

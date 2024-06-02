/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:47:55 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/01 20:14:38 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_parse(char *flags)
{
	int	i;

	i = -1;
	if (!flags || !flags[0])
		return (1);
	if (ft_isdigit(*flags))
		return (print_error(flags, "not a valid identifier"), 0);
	if (*flags == '=' || *flags == '$')
		return (print_error(flags, "not a valid identifier"), 0);
	while (flags[++i])
	{
		if (!flags[i + 1] && flags[i] == '+')
			return (1);
		if ((flags[i] < '0' || flags[i] > '9') && flags[i] != '_' && \
			(flags[i] < 'a' || flags[i] > 'z') && \
			(flags[i] < 'A' || flags[i] > 'Z'))
			return (print_error(flags, "not a valid identifier"), 0);
	}
	return (1);
}

int	build_check(t_minishell *mini, t_list **data, t_pex *pex)
{
	int		q;
	char	**flags;

	q = 0;
	flags = mini->final_cmd[pex->i].cmd;
	if (!flags || !flags[0])
		return (0);
	if (!ft_strncmp(flags[0], "cd", 3))
		(cd_build(flags, mini), ft_pwd(*data, mini), q = 1);
	else if (!ft_strncmp(flags[0], "pwd", 4))
		(pwd_build(mini), q = 1);
	else if (!ft_strncmp(flags[0], "echo", 5))
		(echo_build(flags, mini), q = 1);
	else if (!ft_strncmp(flags[0], "env", 4))
		(env_build(*data, flags[1]), q = 1);
	else if (!ft_strncmp(flags[0], "export", 7))
		(export_build(flags, data), q = 1);
	else if (!ft_strncmp(flags[0], "unset", 6))
		(unset_build(flags, data), q = 1);
	else if (!ft_strncmp(flags[0], "exit", 5))
		(exit_build(mini, flags), q = 1);
	return (q);
}

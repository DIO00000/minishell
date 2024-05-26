/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:47:55 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/25 23:32:45 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_parse(char **flags)
{
	if (!flags[1])
		return (1);
		int i = 1;
	while (flags[i])
	{
		if (ft_isdigit(*flags[i]))
			return (print_error(flags[i], "not a valid identifier"), 0);
		if (*flags[i] == '=' || *flags[i] == '$')
			return (print_error(flags[i], "not a valid identifier"), 0);
		i++;
	}
	return (1);
}

int    build_check(t_minishell *mini, t_list **data, t_pex *pex)
{
	int		q;
	char	*cmd;
	char	**flags;

	q = 0;
	cmd = mini->final_cmd[pex->i].cmd[0];
	flags = mini->final_cmd[pex->i].cmd;
	if (!flags)
		return (0);
	if (!ft_strncmp(flags[0], "cd", 3))
		(cd_build(flags, mini), ft_pwd(*data, mini), q = 1);
	else if (!ft_strncmp(flags[0], "pwd", 4))
		(pwd_build(cmd, mini), q = 1);
	else if (!ft_strncmp(flags[0], "echo", 5))
		(echo_build(flags[1], mini), q = 1);
	else if (!ft_strncmp(flags[0], "env", 4))
		(env_build(*data, flags[1]), q = 1);
	else if (!ft_strncmp(flags[0], "export", 7))
		(export_build(flags, data), q = 1);
	else if (!ft_strncmp(flags[0], "unset", 6))
		(unset_build(flags, data), q = 1);
	else if (!ft_strncmp(flags[0], "exit", 5))
		(exit_build(mini, flags[1]), q = 1);
	return (q);
}

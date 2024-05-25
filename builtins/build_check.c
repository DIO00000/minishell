/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:47:55 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/25 13:52:36 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_parse(char **flags)
{
	if (!flags[1])
		return ;
		int i = 1;
	while (flags[i])
	{
		// printf("FLAGS ==> [%s] i ==>[%d]\n", flags[i], i);
		// if (ft_isdigit(*flags[i]))
		// 	printf("HAHAHAHAHAH\n");
		i++;
	}
}

int    build_check(t_minishell *mini, t_list **data, t_pex *pex)
{
	int		q;
	char	*cmd;
	char	**flags;

	q = 0;
	printf("i ==> %d\n", pex->i);
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
	{
		// export_parse(flags);
		(export_build(flags, data), q = 1);
	}
	else if (!ft_strncmp(flags[0], "unset", 6))
		(unset_build(flags, data), q = 1);
	else if (!ft_strncmp(flags[0], "exit", 5))
		(exit_build(mini, flags[1]), q = 1);
	return (q);
}

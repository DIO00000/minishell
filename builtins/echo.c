/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:06:12 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/28 02:50:38 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*n_flage(char *arg)
{
	int		i;
	char	*tmp;
	char	**args;
	
	i = 0;
	tmp = NULL;
	args = ft_split(arg, "\n");
	free(arg);
	while (args[i])
	{
		arg = ft_strjoin(tmp, args[i]);
		free(tmp);
		tmp = arg;
		i++;
	}
	free_handler(args);
	return (arg);
}

void	echo_build(char	**cmd, t_minishell *mini)
{
	int		i;
	char	*arg;

	i = 1;
	arg = NULL;
	if (cmd[1] && !ft_strncmp(cmd[1], "-n", 2))
	{
		while (cmd[++i])
		{
			arg = n_flage(cmd[i]);
			printf("%s", arg);
			free(arg);
			if (cmd[i + 1])
				printf(" ");
		}
		mini->exit_status = 0;
		return ;
	}
	while (cmd[i])
		printf("%s ", cmd[i++]);
	printf("\n");
	mini->exit_status = 0;
}

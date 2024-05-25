/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:24:39 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/25 12:07:09 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_build(t_minishell *mini, char *status)
{
	if (status)
		(printf("exit\n"), exit(ft_atoi(status)));
	exit(mini->exit_status);
}

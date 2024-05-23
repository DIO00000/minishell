/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:35:05 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/23 18:27:08 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manage_fds(t_minishell *mini)
{
	int	index;

	index = 0;
	while (index < mini->list_size)
	{
		if (!mini->final_cmd[index].redirection_in)
		{
			if (index == 0)
				mini->final_cmd[index].in_fd = open("/dev/stdin", O_RDONLY);
			else
				mini->final_cmd[index].in_fd = -1;
		}
		if (!mini->final_cmd[index].redirection_out)
		{
			if (index == mini->list_size - 1)
				mini->final_cmd[index].out_fd = \
				open("/dev/stdout", O_RDWR | O_TRUNC);
			else
				mini->final_cmd[index].out_fd = -1;
		}
		open_fds(mini, index);
		index++;
	}
}

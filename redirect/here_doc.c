/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 02:08:56 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/29 18:36:06 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_here_doc(t_minishell *mini, t_pex *pex)
// {
// 	char	*str;
// 	char	*s;

// 	str = NULL;
// 	s = ft_strjoin(mini->final_cmd[pex->i].cmd, "\n");
// 	while (1)
// 	{
// 		str = get_next_line(0);
// 		if (!ft_strncmp(str, s, INT_MAX))
// 			return (free(s), fds_closer(pex->end), free(str));
// 		write(pex->end[1], str, ft_strlen(str));
// 		free(str);
// 	}
// }

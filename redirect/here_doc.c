/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 02:08:56 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/31 16:49:29 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_here_doc(t_minishell *mini, t_pex *pex, char *str)
{
	char	*ss;
	char	*s;
	(void)mini;

	ss = NULL;
	s = ft_strjoin(str, "\n");
	while (1)
	{
		str = get_next_line(0);
		if (!ft_strncmp(str, s, INT_MAX))
			return (free(s), fds_closer(pex->end), free(str));
		write(pex->end[1], str, ft_strlen(str));
		free(str);
	}
}

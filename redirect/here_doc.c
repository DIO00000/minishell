/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 02:08:56 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/02 10:09:41 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_here_doc(t_pex *pex, char *lim)
{
	char	*str;
	char	*s;
	int		fd;

	unlink("/tmp/secret_f");
	fd = open("/tmp/secret_f", O_RDWR, O_CREAT, O_TRUNC, 0644);
	if (fd < 0)
		return (free(lim), 0);
	str = NULL;
	s = ft_strjoin(lim, "\n");
	while (1)
	{
		str = readline("heredoc> ");
		if (!ft_strncmp(str, s, INT_MAX))
			return (free(s), free(lim), fds_closer(pex->end), free(str), fd);
		write(fd, str, ft_strlen(str));
		free(str);
	}
	return (0);
}

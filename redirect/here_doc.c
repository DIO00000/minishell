/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 02:08:56 by hbettal           #+#    #+#             */
/*   Updated: 2024/06/03 12:27:36 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_here_doc(char *lim)
{
	char	*str;
	int		fd;

	unlink("/tmp/secret_f");
	fd = open("/tmp/secret_f", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd < 0)
		return (free(lim), 0);
	while (1)
	{
		str = readline("heredoc> ");
		if (!ft_strncmp(str, lim, INT_MAX))
			return (free(lim), free(str), fd);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	return (0);
}

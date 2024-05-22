/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 02:08:56 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/22 16:54:27 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (1);
	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0') && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*join_flags(char **flags, char	*str)
{
	int		i;
	char	*flag;
	
	i = 1;
	str = NULL;
	flag = NULL;
	while (flags[++i])
	{
		str = ft_strjoin_three(flag, " ", flags[i]);
		free(flag);
		flag = str;
	}
	return (str);
}

void	ft_here_doc(t_pex *pex, char *here)
{
	char	*str;
	char	**flags;
	char	*s;

	str = NULL;
	flags = NULL;
	s = NULL;
	flags = ft_split(here, ' ');
	s = ft_strjoin(flags[1], "\n");
	while (1)
	{
		
		str = get_next_line(0);
		if (!ft_strncmp(str, s, INT_MAX))
		{
			pex->split_line[0] = join_flags(flags, str);
			(pex->i--, free(s));
			return (free_handler(flags), fds_closer(pex->end), free(str));
		}
		write(pex->end[1], str, ft_strlen(str));
		free(str);
	}
}

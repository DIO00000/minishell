/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 02:08:56 by hbettal           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/23 22:27:04 by oelharbi         ###   ########.fr       */
=======
/*   Updated: 2024/05/22 16:54:27 by oelharbi         ###   ########.fr       */
>>>>>>> 01d5301dd9f45f1c64a39a1d2ea1d0a72897f057
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

<<<<<<< HEAD
void	ft_here_doc(t_pex *pex, char *here)
{
	char	*str;
	char	**flags;
	char	*s;

	str = NULL;
	flags = NULL;
	s = NULL;
	flags = ft_split(here, " ");
	s = ft_strjoin(flags[1], "\n");
	while (1)
	{
=======
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
		
>>>>>>> 01d5301dd9f45f1c64a39a1d2ea1d0a72897f057
		str = get_next_line(0);
		if (!ft_strncmp(str, s, INT_MAX))
		{
			pex->split_line[0] = join_flags(flags, str);
<<<<<<< HEAD
			pex->i--;
			free(s);
=======
			(pex->i--, free(s));
>>>>>>> 01d5301dd9f45f1c64a39a1d2ea1d0a72897f057
			return (free_handler(flags), fds_closer(pex->end), free(str));
		}
		write(pex->end[1], str, ft_strlen(str));
		free(str);
	}
}

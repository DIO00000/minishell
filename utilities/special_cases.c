/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 07:49:31 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/05 21:42:43 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	str = (char *)s;
	while (str[i] != 0)
		i++;
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return (str + i);
		i--;
	}
	return (NULL);
}

// char	*echo_handler(char *line)
// {
// 	// int i;

// 	// i = 0;
// 	// if (line[i] == "\"")
// 	// {
// 	// 	while ()
// 	// }
// }

// char	*special_cases(char **lines, char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (lines[i])
// 	{
// 		if (!ft_strncmp(lines[i], "echo ", 5))
// 			return (echo_handler(lines[i]));
// 	}
// }

char	*ft_strjoin_three(char *s1, char *buff, char *s2)
{
	char	*all;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strjoin(buff, s2));
	if (!buff)
		return (ft_strjoin(s1, buff));
	all = (char *)malloc(ft_strlen(s1) + ft_strlen(buff) + ft_strlen(s2) + 1);
	if (!all)
		return (NULL);
	while (s1[i])
		all[j++] = s1[i++];
	i = 0;
	while (buff[i])
		all[j++] = buff[i++];
	i = 0;
	while (s2[i])
		all[j++] = s2[i++];
	all[j] = 0;
	return (all);
}

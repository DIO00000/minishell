/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 07:49:31 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/20 21:50:41 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

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

char	**split_token(char *line)
{
	char	**split;
	char	*sp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	split = ft_split(line, '>');
	sp = ft_strjoin(split[0], split[1]);
	sp = ft_strjoin(sp, split[2]);
	split = ft_split(sp, ' ');
	split[2] = malloc(sizeof(char) * 2);
	while (line[i] != '>' && line[i])
		i++;
	if (line[i] == '>')
	{
		split[2][0] = '>';
		split[2][1] = 0;
	}
	return (split);
}

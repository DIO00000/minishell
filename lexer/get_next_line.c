/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 22:23:18 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/20 05:00:59 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(char *s, char c)
{
	while (*s != c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return (s);
}

char	*print_the_line(char *line)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	result = malloc(i + 1);
	if (!result)
		return (NULL);
	while (j < i)
	{
		result[j] = line[j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

char	*rest_line(char *line)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	result = malloc((ft_strlen(line + i)) + 1);
	if (!result)
		return (free(line), line = NULL, NULL);
	while (line[i])
		result[j++] = line[i++];
	result[j] = '\0';
	return (free(line), line = NULL, result);
}

char	*get_the_line(char	*str, int fd)
{
	char	*s;
	int		i;

	s = malloc((size_t)BUFFER_SIZE + 1);
	if (!s)
		return (free(str), str = NULL, NULL);
	i = 1;
	while (i > 0 && ft_strchr(str, '\n') == 0)
	{
		i = read(fd, s, BUFFER_SIZE);
		if (i == -1)
			return (free(str), str = NULL, free(s), s = NULL, NULL);
		s[i] = '\0';
		str = ft_join(str, s);
		if (!str)
			break ;
	}
	return (free(s), str);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (!line)
		line = ft_strdup("");
	if (!line)
		return (NULL);
	line = get_the_line(line, fd);
	if (!line)
		return (NULL);
	if (line[0] == '\0')
		return (free(line), line = NULL, NULL);
	str = print_the_line(line);
	if (!str)
		return (free(line), line = NULL, NULL);
	line = rest_line(line);
	return (str);
}

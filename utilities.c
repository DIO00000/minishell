/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:28:33 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/19 15:38:00 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

char	*where_path(char **env)
{
	int		i;
	int		j;
	char	*name;

	name = "PATH=";
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] == name[j])
		{
			if (!name[j + 1])
				return (env[i] + 5);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*ft_strdup(char *s1)
{
	size_t		i;
	size_t		lent;
	char		*dest;

	i = 0;
	lent = ft_strlen(s1);
	dest = (char *)malloc(lent + 1);
	if (dest == NULL)
		return (NULL);
	while (s1[i] != 0)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*all;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	all = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!all)
		return (NULL);
	while (s1[i])
		all[j++] = s1[i++];
	i = 0;
	while (s2[i])
		all[j++] = s2[i++];
	all[j] = 0;
	return (all);
}


void	ft_putnbr_fd(int n, int fd)
{
	long	s;

	s = (long)n;
	if (s < 0)
	{
		ft_putchar_fd('-', fd);
		s *= -1;
	}
	if (s / 10)
		ft_putnbr_fd((s / 10), fd);
	ft_putchar_fd((s % 10) + 48, fd);
}

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
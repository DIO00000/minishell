/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 10:12:29 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/16 21:45:08 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_thechar(char s, char *c)
{
	int	i;

	i = 0;
	while (c[i])
		if(s == c[i++])
			return (1);
	return (0);
}


int	ft_words(const char *s, char *c)
{
	int		i;
	int		count;
	char	quote;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (is_thechar(s[i], c) && s[i])
			i++;
		if (s[i])
			count++;
		while (s[i] && !is_thechar(s[i], c))
		{
			if (s[i] == '\"' || s[i] == '\'')
			{
				quote = s[i++];
				while (s[i] && s[i] != quote)
					i++;
			}
			if (s[i])
				i++;
		}
	}
	return (count);
}
#include <stdio.h>

int	the_word(char *s, char *c)
{
	int		len;
	char	quote;

	len = 0;
	while (s[len] && !is_thechar(s[len], c))
	{
		if (s[len] == '\'' || s[len] == '\"')
		{
			quote = s[len++];
			while (s[len] && s[len] != quote)
				len++;
			if (!s[len])
				return (len);
		}
		len++;
	}
	return (len);
}

void	ft_free(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
		free((*arr)[i++]);
	free(*arr);
}

static char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	**ft_split(char *s, char *c)
{
	size_t		i;
	size_t		counter;
	char		**words;

	i = 0;
	if (!s)
		return (NULL);
	counter = ft_words(s, c);
	words = malloc((counter + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	while (i < counter)
	{
		while (*s && is_thechar(*s, c))
			s++;
		words[i] = malloc(the_word(s, c) + 1);
		if (!words[i])
			return (ft_free(&words), NULL);
		ft_strncpy(words[i], s, the_word(s, c));
		words[i++][the_word(s, c)] = '\0';
		s = s + the_word(s, c);
	}
	words[i] = NULL;
	return (words);
}

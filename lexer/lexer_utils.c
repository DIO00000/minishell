/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 00:07:47 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/13 01:17:46 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isoperator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_isqoute(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	ft_iswhitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	get_qoute_index(char *str, int i)
{
	char	qoute;

	qoute = str[i - 1];
	while (str[i] && str[i] != qoute)
		i++;
	if (!str[i])
		return (i - 1);
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*tp_dest;
	char	*tp_src;
	size_t	i;

	tp_dest = (char *) dst;
	tp_src = (char *) src;
	i = 0;
	if (tp_dest == NULL && tp_src == NULL)
		return (NULL);
	while (i < n)
	{
		tp_dest[i] = tp_src[i];
		i++;
	}
	return (tp_dest);
}

void	*ft_memmove(void *dst, void *src, size_t len)
{
	char	*dest;
	char	*source;

	if (!dst && !src)
		return (NULL); 
	dest = (char *)dst;
	source = (char *)src;
	if (dst < src)
		ft_memcpy(dst, src, len);
	else if (dst > src)
	{
		while (len > 0)
		{
			len--;
			dest[len] = source[len];
		}
	}
	return (dst);
}

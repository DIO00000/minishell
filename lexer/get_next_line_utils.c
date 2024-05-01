/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 22:23:27 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/01 12:14:05 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


size_t	ft_strlcpy(char *dest, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1 && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	len;
	size_t	src_len;

	src_len = ft_strlen(src);
	len = 0;
	if (!dst && dstsize == 0)
		return (src_len);
	while (*dst && dstsize > 0)
	{
		dst++;
		len++;
		dstsize--;
	}
	while (*src && dstsize > 1)
	{
		*dst = *src;
		dst++;
		src++;
		dstsize--;
	}
	if (dstsize == 1 || *src == 0)
		*(dst) = '\0';
	return (src_len + len);
}

char	*ft_strjoin(char *s1, char *buff)
{
	char	*str;
	int		i;
	int		x;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!buff)
		return (free(s1), NULL);
	i = ft_strlen(s1);
	x = ft_strlen(buff) + ft_strlen(s1) + 1;
	str = malloc(x);
	if (!str)
		return (free(s1), s1 = NULL, NULL);
	ft_strlcpy(str, s1, i + 1);
	ft_strlcat(str, buff, x);
	return (free(s1), s1 = NULL, str);
}

// char	*ft_strdup(char *str)
// {
// 	char	*new;
// 	int		i;
// 	int		len;

// 	i = 0;
// 	len = ft_strlen(str);
// 	new = malloc((len + 1) * sizeof(char));
// 	if (!new)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		new[i] = str[i];
// 		i++;
// 	}
// 	new[i] = '\0';
// 	return (new);
// }

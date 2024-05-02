/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 22:23:27 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/01 21:36:56 by hbettal          ###   ########.fr       */
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
	char	*all;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 && !buff)
		return (NULL);
	if (!s1)
		return (ft_strdup(buff));
	if (!buff)
		return (ft_strdup(s1));
	all = (char *)malloc(ft_strlen(s1) + ft_strlen(buff) + 1);
	if (!all)
		return (NULL);
	while (s1[i])
		all[j++] = s1[i++];
	i = 0;
	while (buff[i])
		all[j++] = buff[i++];
	all[j] = 0;
	return (all);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:55:38 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/23 20:41:26 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_start_t(char *s1, char *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

static int	ft_end_t(char *s1, char *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (i > 0)
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i--;
	}
	return (i + 1);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		start;
	int		end;
	char	*string;

	if (!s1 || !set)
		return (NULL);
	end = ft_end_t(s1, set);
	start = ft_start_t(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	string = malloc((end - start) + 1);
	if (string == NULL)
		return (NULL);
	ft_strlcpy(string, s1 + start, (end - start) + 1);
	return (string);
}

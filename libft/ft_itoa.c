/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 20:28:05 by oelharbi          #+#    #+#             */
/*   Updated: 2023/11/21 16:13:16 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_length(int num)
{
	long	n;
	int		count;

	count = 1;
	n = (long)num;
	while (n / 10)
	{
		n = n / 10;
		count++;
	}
	if (n < 0)
		return (count + 1);
	return (count);
}

static char	*return_string(int n, int i)
{
	int		count;
	char	*str;
	long	num;

	num = (long)n;
	count = str_length(num);
	str = malloc((count + 1));
	if (str == NULL)
		return (NULL);
	if (num < 0)
	{
		num *= -1;
		str[0] = '-';
	}
	i = count - 1;
	while (num >= 10)
	{
		str[i] = (num % 10) + 48;
		i--;
		num /= 10;
	}
	str[i] = num + 48;
	i = count;
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = 0;
	str = return_string(n, i);
	return (str);
}

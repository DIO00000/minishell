/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers_utlis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:43:43 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/13 18:06:53 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	no_overflow(int sign, unsigned long long n, int count)
{
	if ((n > LLONG_MAX || count > 19) && sign == -1)
		return (0);
	if ((n > LLONG_MAX || count > 19) && sign == 1)
		return (-1);
	return (n * sign);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					count;
	int					sign;
	unsigned long long	n;

	i = 0;
	count = 0;
	sign = 1;
	n = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i++] - '0');
		count++;
	}
	return (no_overflow(sign, n, count));
}

static int	len_int(long nbr)
{
	int	ccount;

	ccount = 0;
	if (nbr < 0)
	{
		ccount++;
		nbr *= -1;
	}
	if (nbr == 0)
	{
		ccount++;
	}
	while (nbr)
	{
		if (nbr > 0)
		{
			nbr /= 10;
			ccount++;
		}
	}
	return (ccount);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		l;
	long	nbr;

	nbr = n;
	l = len_int(nbr);
	num = (char *) malloc (l + 1);
	if (!num)
		return (NULL);
	num[l] = '\0';
	l--;
	if (nbr == 0)
		num[0] = 0 + 48;
	if (nbr < 0)
	{
		nbr *= -1;
		num[0] = '-';
	}
	while (nbr > 0)
	{
		num[l] = nbr % 10 + 48;
		nbr /= 10;
		l--;
	}
	return (num);
}
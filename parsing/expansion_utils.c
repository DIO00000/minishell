/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:43:05 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/22 12:48:41 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expansion_counter(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		(*str == '$') && (count++);
		str++;
	}
	return (count);
}

int	ft_start(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (0);
		}
		if (str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}

int	ft_end(char *str, int start)
{
	while (ft_isalnum(str[start]) || str[start] == '_')
		start++;
	return (start);
}

int	expansion_error(char c)
{
	if (c == '_' || c == '?')
		return (0);
	else if (!ft_isalpha(c))
		return (1);
	return (0);
}

void	exit_number(t_minishell *mini, char **str, int start)
{
	char	*exit;

	exit = ft_itoa(mini->exit_status);
	if (!exit)
		ft_exit(mini, NULL, NULL, 12);
	*str = remove_str(str, exit, start, 1);
	if (!(*str))
		ft_exit(mini, NULL, NULL, 12);
	free(exit);
}

char	*remove_str(char **str, char *env, int start, int len)
{
	char	*result;
	int		j;
	int		i;

	(1 == 1) && (j = 0, i = 0);
	result = zyalloc(((ft_strlen(*str) - len - 1)\
		+ ft_strlen(env) + 1), 'a', true);
	while ((*str)[i])
	{
		if (i == start - 1)
		{
			i += len + 1;
			while (env && *env)
			{
				result[j++] = *env;
				env++;
			}
			continue ;
		}
		result[j++] = (*str)[i++];
	}
	return (result[j] = '\0', free(*str), result);
}

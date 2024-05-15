/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbettal <hbettal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:00:49 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/14 22:09:52 by hbettal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_shift(char *str, int start, int end, int shifter)
{
	ft_memmove(&(str[end]), &(str[start]), ft_strlen(&(str[start])) + 1);
	if (shifter == -1)
		str[start] = ' ';
	if (shifter == 1)
		str[end] = ' ';
}

char	*put_spaces(char *str, int space_counter)
{
	int	i;
	int	j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc((ft_strlen(str) + space_counter + 1) * sizeof(char));
	if (!new_str)
		ft_error("minishell: ", "malloc failed");
	ft_strlcpy(new_str, str, ft_strlen(str) + space_counter + 1);
	free(str);
	while (new_str[i])
	{
		if (ft_isqoute(new_str[i]))
			i = get_qoute_index(new_str, i + 1);
		else if (ft_isoperator(new_str[i]))
		{
			if (i > 0 && !ft_iswhitespace(new_str[i - 1]))
				(ft_shift(new_str, i, i + 1, -1), i++);
			if (new_str[i] != '|')
				while(new_str[i + 1] == '<' || new_str[ + 1] == '>')
					i++;
			if (!ft_iswhitespace(new_str[i + 1]) && new_str[i + 1] != '\0')
				(ft_shift(new_str, i, i + 1, 1), i++);
		}
		i++;
	}
	return (new_str);
}

int	ft_count_spaces(char *str)
{
	int	i;
	int	space_counter;
	int	is_space;

	i = 0;
	space_counter = 0;
	is_space = 0;
	while (str[i])
	{
		if (ft_isqoute(str[i]))
			i = get_qoute_index(str, i + 1);
		else if (ft_isoperator(str[i]))
		{
			if (i > 0 && !ft_iswhitespace(str[i - 1]))
				space_counter++;
			if (str[i] != '|')
				while(str[i + 1] == '<' || str[i + 1] == '>')
					i++;
			if (!ft_iswhitespace(str[i + 1]) && str[i + 1] != '\0')
			{
				space_counter++;
				is_space = 1;	
			}
		}
		else
			is_space = 0;
		i++;
	}
	return (space_counter);
}

void	lexer(t_minishell *minishell)
{
	int	i;
	int	space_counter;
	
	i = 0;
	space_counter = ft_count_spaces(minishell->trimed_cmd);
	if (space_counter == 0)
	{
		minishell->cmd = ft_split(minishell->trimed_cmd, ' ');
		if (!minishell->cmd)
			ft_error("minishell: ", "malloc failed");
		// free(minishell->trimed_cmd);
	}
	minishell->trimed_cmd = put_spaces(minishell->trimed_cmd, space_counter);
	if (!minishell->trimed_cmd)
		ft_error("minishell: ", "malloc failed");
	minishell->cmd = ft_split(minishell->trimed_cmd, ' ');
	if (!minishell->cmd)
		ft_error("minishell: ", "malloc failed");
	// free(minishell->trimed_cmd);
}

// int	isempty_line(t_minishell *minishell)
// {
// 	int	end;
	
// 	end = ft_strlen(minishell->trimed_cmd) - 1;
// 	if (minishell->trimed_cmd[0] == '~' && ft_strlen(minishell->trimed_cmd) == 1)
// 	{
// 		printf("%s: %s%s: %s\n", "minishell", "/Users/", minishell->username, "is a directory");
// 		return (1);
// 	}
// 	if ((minishell->trimed_cmd[0] == '>' && minishell->trimed_cmd[1] == '>' && minishell->trimed_cmd[2] == '>') || (minishell->trimed_cmd[0] == '<' && minishell->trimed_cmd[1] == '<' && minishell->trimed_cmd[2] == '<'))
// 	{
// 		if (minishell->trimed_cmd[0] == '>')
// 			printf("%s: %s\n", "minishell", "syntax error near unexpected token `>'");
// 		else
// 			printf("%s: %s\n", "minishell", "syntax error near unexpected token  `newline'");
// 		return (1);
// 	}
// 	if (minishell->trimed_cmd[0] == '"' && minishell->trimed_cmd[1] == '"' && ft_strlen(minishell->trimed_cmd) == 2)
// 	{
// 		printf("%s: : %s\n", "minishell", "command not found");
// 		minishell->cmd_excuted = 0;
// 		return (1);
// 	}
// 	if (minishell->trimed_cmd[0] == '|' || minishell->trimed_cmd[end] == '|')
// 	{
// 		printf("%s: %s\n", "minishell", "syntax error near unexpected token `|'");
// 		return (1);
// 	}
// 	return (0);
// }

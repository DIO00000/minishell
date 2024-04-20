/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:37:21 by oelharbi          #+#    #+#             */
/*   Updated: 2024/04/20 21:08:41 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    prompt_custom(t_minishell *minishell)
{
    char    *username;
    char    *final;
    char    *n_arrow;
    char    *cur_dir;
    char    *dir;
    
    if (minishell->trm_prompt != NULL)
        free(minishell->trm_prompt);
    cur_dir = get_dir();
    if (minishell->cmd_excuted == 1)
        username = ft_strjoin(GREEN_ARROW, minishell->username);
    else
        username = ft_strjoin(RED_ARROW, minishell->username);
    dir = ft_strjoin(SPC, cur_dir);
    n_arrow = ft_strjoin(username, dir);
    final = ft_strjoin(n_arrow, X);
    free(username);
    free(dir);
    free(n_arrow);
    free(cur_dir);
    minishell->trm_prompt = final;
    minishell->cmd_excuted = 1;
}

char    *get_dir(void)
{
    int i;
    char *pwd;
    char **split;
    char *dir;

    i = 0;
    pwd = getcwd(NULL, 0);
    printf("cur_dir: %s\n", pwd);
    if (ft_strncmp(pwd, "/", ft_strlen(pwd)) == 1)
        dir = ft_strdup("/");
    else
    {
        split = ft_split(pwd, '/');
        while (split[i])
            i++;
        dir = ft_strdup(split[i - 1]);
        free_handler(split);
    }
    return (dir);
}
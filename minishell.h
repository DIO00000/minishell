/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:46:47 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/07 23:07:24 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include <stdio.h>
// # include <unistd.h>
// # include <stdlib.h>
// # include <fcntl.h>
// # include <readline/readline.h>
// # include <readline/history.h>

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>
# include <string.h>
# include <sys/stat.h>
# include <termios.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdarg.h>


// typedef enum s_tnum
// {
// 	COMMAND,
// 	PYPE,
// 	VARIABLE,
// 	SPACE,
// 	REDIRECTION_IN,
// 	REDIRECTION_OUT,
// 	SINGLE_QUOTE,
// 	DOUBLE_QUOTE,
// 	HERDOC,
// }	t_tnum;

#define GREEN_ARROW "\001\e[1m\e[32m➜  \001\e[1m\e[34m\002"
#define RED_ARROW "\001\e[1m\e[31m➜  \001\e[1m\e[34m\002"
#define SPC "\001\e[1m\e[33m\002 "
#define X "\001\e[1m\e[33m\002 ✘ \001\e[0m\002"
# define SPACES " \t\n\v\r\f"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

// struct

typedef struct s_list
{
	char	*env;
	int		index;
	struct s_list *next;
}	t_list;

typedef struct s_pex
{
	int		i;
	int		end[2];
	int		input;
	char	**split_line;
	int		lines;
}	t_pex;

typedef struct s_minishell
{
	char	*cmd_line;
	char	**new_env;
	char	*cmd_path;
	t_list	**data;
	char	*defult_path;
	char	*input;
	int		signal;
	int		*pids;
	int		table_size;
	int		env_status;
	int		syntax;
	struct termios	term;
	char	*username;
	int		cmd_excuted;
	int		shlvl;
	char	*trm_prompt;
	char	*last_dir;
	char	*curr_dir;
	char	*buffer;
	char	*trimed_cmd;
}	t_minishell;

//signals

void	signals(struct termios *term);
void	remove_c(struct termios *term);
void    sig_init(int    signum);

char    *get_dir(t_minishell *minishell);
void    prompt_custom(t_minishell *minishell);

// Parsing 

void    ft_error(char *str, char *msg);

// buildtins

int		build_check(char *cmd, t_minishell *mini, t_list **data);
void    cd_build(char **cmd, t_minishell *mini);
void	pwd_build(char *pwd, t_minishell *mini);
void	echo_build(char	*cmd);
t_list	*fill_env(char **origin_env, t_list *data, t_minishell *mini);
void	env_build(t_list *data, t_minishell *mini, char *cmd);
void	export_build(char **var, t_list **data);
void	unset_build(char **var, t_list **data);
void	indexer(t_list **data);
t_list	*var_finder(char *var, t_list **data);

// Excuting

char	**split_token(char *line); 
char	**ft_split(char *s, char c);
void	read_command(t_minishell *mini, t_list **data);
char	*ft_strjoin_h(char *s1, char *s2);
void	fds_closer(int end[]);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strdup(char *s1);
char	*where_path(t_list *data);
size_t	ft_strlen(char *s);
void	free_handler(char **str);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	ft_here_doc(int end[], int ac, char **av);
int		count_words(char *str, char c);
void	special_cases(char **lines, char **env);
void    handler(void);
void    sig_quit(int    signum);
void    sig_init(int    signum);
void	first_red(char **token);
char	**last_red(char *line);

//readline

int	*read_line(t_minishell *minishell);

// Utilities

void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_strrchr(const char *s, int c);
void	ft_lstdelone(t_list *lst);
void	ft_lstdel_mid(t_list **data, t_list *rm);
void	ft_lstclear(t_list **lst);
t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strjoin_three(char *s1, char *buff, char *s2);
char	*ft_strjoin(char *s1, char *buff);

//get_next_line

size_t	ft_strlcpy(char *dest, char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strchr(char *s, char c);
char	*print_the_line(char *line);
char	*rest_line(char *line);
char	*get_the_line(char	*str, int fd);
char	*get_next_line(int fd);
char	*ft_strdup(char *str);


//lexer
int	isempty_line(t_minishell *minishell);
int	lexer(t_minishell *minishell);


#endif

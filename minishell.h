/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:46:47 by hbettal           #+#    #+#             */
/*   Updated: 2024/04/20 15:46:28 by oelharbi         ###   ########.fr       */
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

int		is_cntl_c;


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

typedef struct s_type
{
	char	*string;
	int		type;
	struct s_type	*next;
}	t_type;

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
	t_type	*type;
	char	*cmd_line;
	char	**env;
	char	*input;
	int		signal;
	int		*pids;
	int		table_size;
	int		env_status;
	int		syntax;
	struct termios	term;
}	t_minishell;

//signals
void	signals(struct termios *term);
void	remove_c(struct termios *term);
void	ctrl_c(void);
void    sig_init(int    signum);
void	ctrl_backslash(void);



// Parsing 

void    ft_error(char *str, char *msg);



// Excuting

char	**ft_split(char *s, char c);
void	read_command(char **env);
char	*ft_strjoin(char *s1, char *s2);
void	fds_closer(int end[]);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strdup(char *s1);
char	*where_path(char **env);
size_t	ft_strlen(const char *s);
void	free_handler(char **str);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	ft_here_doc(int end[], int ac, char **av);
int		count_words(char *str, char c);
void	special_cases(char **lines, char **env);
void    handler(void);
void    sig_quit(int    signum);
void    sig_init(int    signum);


// Utilities

void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);

#endif
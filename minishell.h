/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:04:22 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/18 14:46:54 by oelharbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H



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
# include <sys/types.h>
# include <dirent.h>
# include <stdarg.h>
# include "libft/libft.h"

#define PIPE 1
#define REDIN 2
#define HERDOC 3
#define LIM 4
#define REDOUT 5
#define COMMAND 6
#define ARGUMENT 7
#define FILE 8
#define ERROR 9
#define APPEND 10




// #define MINI "\033[1;36m\033[1;32m➜ \033[0m\033[1;33mminishell\033[2;30m -\033[0m\033[1;36m\033[1;32m ✘ \033[0m"
#define GREEN_ARROW "\001\e[1m\e[32m➜  \001\e[1m\e[34m\002"
#define SPC "\001\e[1m\e[33m\002 "
#define X "\001\e[1m\e[33m\002 ✘ \001\e[0m\002"
# define SPACES " \t\n\v\r\f"


typedef enum	e_parse_state {
    START,
    IN_COMMAND,
    IN_ARG,
    IN_FILE,
    IN_HEREDOC
}	t_parse_state;

typedef struct s_parser
{
	char			*string;
	int				class;
	struct s_parser	*next;
}	t_parser;

//	COMMAND_TABLE (PIPELINE)
typedef struct s_table
{
	char		**line;
	int			infd;
	int			outfd;
	t_parser	*redin;
	t_parser	*redout;
}	t_table;


typedef struct s_minishell
{
	t_parser *lst;
	t_table	*table;
	char	**cmd;
	char	**new_env;
	char	*cmd_path;
	int		exit_status;
	char	*defult_path;
	char	*input;
	int		signal;
	int		*pids;
	int		table_size;
	int		env_status;
	int		syntax;
	struct termios	term;
	int		cmd_excuted;
	char	*buffer;
	char	*trm_prompt;
	char	*username;
	char	*last_dir;
	char	*curr_dir;
	
}	t_minishell;

//prompt
void    prompt_custom(t_minishell *minishell);
char    *get_dir(t_minishell *minishell);

// #define malloc(x) NULL
//signals
void    sig_init(int    signum);
void	signals(struct termios *term);
void	remove_c(struct termios *term);


//readline
void	read_line(t_minishell *mini);

//lexer
int		ft_count_spaces(char *str);
void	lexer(t_minishell *minishell);
char	*put_spaces(char **str, int space_counter);
void	ft_shift(char *str, int start, int end, int shifter);

//lexer_utils
int		ft_iswhitespace(char c);
int		ft_isoperator(char c);
int		ft_isqoute(char c);
int		get_quote_index(char *str, int i);
char	*ft_join(char *s1, char *buff);

//parsing
void	parsing(t_minishell *mini);
void	classification(t_minishell *mini);

//parsing_utils
void		lstadd_back(t_parser **lst, t_parser *new);
t_parser	*lstlast(t_parser *lst);
t_parser	*lstnew(void *content);
int			count_quote(char *str);
void		lstclear(t_parser **lst);
char		*remove_quotes(char **str, int count_quotes);
void		handle_redirection(t_parser *current, int class);


//expansion
void	parameter_expansion(t_minishell *mini, char *current);

//expansion_utils
int	expansion_counter(char *str);


//test

void	ft_exit(t_minishell *mini, char *cmd, char *str, int ext);
void	free_strings(char **strings);



#endif
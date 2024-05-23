/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2024/05/16 12:04:22 by oelharbi          #+#    #+#             */
/*   Updated: 2024/05/23 22:29:48 by oelharbi         ###   ########.fr       */
=======
/*   Created: 2024/04/02 14:46:47 by hbettal           #+#    #+#             */
/*   Updated: 2024/05/22 16:54:08 by oelharbi         ###   ########.fr       */
>>>>>>> 01d5301dd9f45f1c64a39a1d2ea1d0a72897f057
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES

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
# include <stdbool.h>
# include <fcntl.h>

// CLASSES

# define PIPE 1
# define REDIN 2
# define HERDOC 3
# define LIM 4
# define REDOUT 5
# define COMMAND 6
# define ARGUMENT 7
# define FILE 8
# define ERROR 9
# define APPEND 10
# define QUOTE_ERR 11

// DEFINES

# define GREEN_ARROW "\001\e[1m\e[32m➜  \001\e[1m\e[34m\002"
# define X "\001\e[1m\e[33m\002 minishell ✘ \001\e[0m\002"
# define SPACES " \t\n\v\r\f"
# define SPC "\001\e[1m\e[33m\002 "

// GET_NEXT_LINE

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

// STRUCTS

typedef struct s_pex
{
	int		i;
	int		end[2];
	int		input;
	char	**split_line;
	int		lines;
}	t_pex;

typedef struct s_list
{
	char			*env;
	int				index;
	struct s_list	*next;
}	t_list;

typedef enum e_parse_state
{
	START,
	IN_COMMAND,
	IN_ARG,
	IN_FILE,
	IN_HEREDOC
}			t_parse_state;

typedef struct s_garbage
{
	void				*adr;
	bool				is_free;
	struct s_garbage	*next;
}		t_garbage;

typedef struct s_exp_helper
{
	int		exp_counter;
	int		start;
	int		end;
	char	*exp_name;
	char	*exp_env;
}		t_exp_helper;

typedef struct s_parser
{
	char			*string;
	int				class;
	struct s_parser	*next;
}		t_parser;

typedef struct s_final_st
{
	char		**cmd;
	int			in_fd;
	int			out_fd;
	t_parser	*redirection_in;
	t_parser	*redirection_out;
}	t_final_st;

typedef struct s_minishell
{
	t_parser		*lst;
	t_final_st		*final_cmd;
	int				list_size;
	char			**cmd;
	char			**new_env;
	char			*cmd_path;
	int				exit_status;
	char			*defult_path;
	char			*input;
	int				signal;
	int				*pids;
	int				env_status;
	int				syntax;
	struct termios	term;
<<<<<<< HEAD
	char			*buffer;
	char			*trm_prompt;
	char			*username;
	char			*last_dir;
	char			*curr_dir;
	t_list			**data;
}		t_minishell;

//  #define malloc(x) NULL
// SIGNALS

void		signals(struct termios *term);
void		sig_init(int signum);
void		remove_c(struct termios *term);
void		sig_quit(int signum);

// READLINE

void		read_line(t_minishell *mini);

// LEXER

int			ft_count_spaces(char *str);
void		lexer(t_minishell *minishell);
char		*put_spaces(char **str, int space_counter);
void		ft_shift(char *str, int start, int end, int shifter);

// LEXER_UTILS

int			ft_iswhitespace(char c);
int			ft_isoperator(char c);
int			ft_isqoute(char c);
int			get_quote_index(char *str, int i);
char		*ft_join(char *s1, char *buff);

// PARSING

int			parsing(t_minishell *mini);
void		classification(t_minishell *mini);
void		parameter_expansion(t_minishell *mini, t_parser *current);

// PARSING_UTILS

void		lstadd_back(t_parser **lst, t_parser *new);
t_parser	*lstlast(t_parser *lst);
t_parser	*lstnew(void *content);
int			count_quote(char *str);
void		lstclear(t_parser **lst);
char		*remove_quotes(char **str, int count_quotes);
void		handle_redirection(t_parser *current, int class);
int			expansion_counter(char *str);
int			ft_start(char *str);
int			ft_end(char *str, int start);
int			expansion_error(char c);
void		exit_number(t_minishell *mini, char **str, int start);
char		*remove_str(char **str, char *envvar, int start, int len);
void		syntax_printer(char *str);
int			systax_error(t_parser *lst);
void		ft_exit(t_minishell *mini, char *cmd, char *str, int ext);
void		free_strings(char **strings);
void		print_error(char *var, char *msg);

// STCURT_TO_EXECUTE

int			lstsize(t_parser *lst);
int			struct_cmd(t_minishell *mini);
int			set_cmd_line(t_minishell *mini, int i);
int			get_cmd_size(t_minishell *mini, int i);
t_parser	*get_pipe(t_parser *lst, int i);
void		ft_close_fds(t_minishell *mini);
int			open_files(t_minishell *mini, int i);
void		manage_fds(t_minishell *mini);
void		open_fds(t_minishell *mini, int i);
int			open_infd(t_parser *curr, t_parser *redirecyion_in);
int			open_outfd(t_parser *curr, t_parser *redirecyion_out);

// UTILS

void		ft_putchar_fd(char c, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char *s, char *c);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dest, const char *src, size_t dstsize);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, void *src, size_t len);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strdup(const char *s1);
char		*ft_substr(const char *s, unsigned int start, size_t len);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
char		*ft_itoa(int n);
int			ft_isdigit(int c);
char		*ft_strjoin(char const *s1, char const *s2);

// PROMPT
void		prompt_custom(t_minishell *minishell);
char		*get_dir(t_minishell *minishell);

// GARBAGE_COLLECTOR

void		*zyalloc(size_t size, int flag, bool is_free);

/******************** ===> EXCUTION	<=== ********************/

// BUILDTIONS

int			build_check(char *cmd, t_minishell *mini, t_list **data);
void		cd_build(char **cmd, t_minishell *mini);
void		pwd_build(char *pwd, t_minishell *mini);
void		echo_build(char	*cmd);
t_list		*fill_env(char **origin_env, t_list *data, t_minishell *mini);
void		env_build(t_list *data, char *cmd);
void		export_build(char **var, t_list **data);
void		unset_build(char **var, t_list **data);
void		indexer(t_list **data);
t_list		*var_finder(char *var, t_list **data);
void		ft_shlvl(t_list *data, t_minishell *m);
void		ft_pwd(t_list	*data, t_minishell *m);

// EXCUTING

void	single_command(char *line, t_minishell *mini, t_list **data);
char		*path_check(char *command, t_list *data, int end[]);
void		read_command(t_minishell *mini, t_list **data);
void		fds_closer(int end[]);
char		*where_path(t_list *data);
void		free_handler(char **str);
void		ft_here_doc(t_pex *pex, char *here);
int			count_words(char *str, char c);
char		**first_red(char **token);
char		**last_red(char *line);
void		last_cmd(int end[], char *line, t_list **data, t_minishell *mini);
void		more_commands(t_pex *pex, t_list **data, t_minishell *mini);

// UTILITIES

char		*ft_strrchr(const char *s, int c);
void		ft_lstdelone(t_list *lst);
void		ft_lstdel_mid(t_list **data, t_list *rm);
void		ft_lstclear(t_list **lst);
t_list		*ft_lstnew(char *content);
void		ft_lstadd_back(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
char		*ft_strtrim(char *s1, char *set);
char		*ft_strjoin_three(char *s1, char *buff, char *s2);
int			ft_atoi(const char *str);
void		free_handler(char **str);
void		fds_closer(int end[]);

//GET_NEXT_LINE

char		*ft_strchr(char *s, char c);
char		*print_the_line(char *line);
char		*rest_line(char *line);
char		*get_the_line(char	*str, int fd);
char		*get_next_line(int fd);
char		*ft_join(char *s1, char *buff);

#endif
=======
	char	*username;
	int		cmd_excuted;
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
void	env_build(t_list *data, char *cmd);
void	export_build(char **var, t_list **data);
void	unset_build(char **var, t_list **data);
void	indexer(t_list **data);
t_list	*var_finder(char *var, t_list **data);
void	ft_shlvl(t_list *data, t_minishell *m);
void	ft_pwd(t_list	*data, t_minishell *m);

// Excuting

char	*path_check(char *command, t_list *data, int end[]);
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
void	ft_here_doc(t_pex *pex, char *here);
int		count_words(char *str, char c);
void	special_cases(char **lines, char **env);
void    handler(void);
void    sig_quit(int    signum);
void    sig_init(int    signum);
char	**first_red(char **token);
char	**last_red(char *line);
void	last_cmd(int end[], char *line, t_list **data, t_minishell *mini);
void	more_commands(t_pex *pex, t_list **data, t_minishell *mini);

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
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

//get_next_line

size_t	ft_strlcpy(char *dest, char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strchr(char *s, char c);
char	*print_the_line(char *line);
char	*rest_line(char *line);
char	*get_the_line(char	*str, int fd);
char	*get_next_line(int fd);
char	*ft_strdup(char *str);
char	*ft_join(char *s1, char *buff);


//lexer
// int	isempty_line(t_minishell *minishell);
int	ft_count_spaces(char *str);
void	lexer(t_minishell *minishell);

//lexer_utils
int		ft_iswhitespace(char c);
int		ft_isoperator(char c);
int		ft_isqoute(char c);
int		get_qoute_index(char *str, int i);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, void *src, size_t len);

#endif
>>>>>>> 01d5301dd9f45f1c64a39a1d2ea1d0a72897f057

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:38:17 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 16:03:00 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>

# define VIOLET "\033[35m"
# define RESET "\033[0m"
# define GREEN "\033[38;5;10m"
# define BLANC "\033[37m"

extern int	g_exit_status;

typedef struct s_pipex
{
	int		**fd;
	int		**fd_hd;
	int		*here_doc;
	int		*app_end;
	int		*pid;
	char	***cmd;
	char	**limiter;
	char	**file_in;
	char	**file_out;
	int		*f_in;
	int		*f_out;
	char	**path;
	int		n_cmd;
}	t_pipex;

typedef struct s_shell_data_prompt
{
	char		**env;
	char		**cmd;
	char		*prompt;
	char		*prev_input;
	t_list		*lst_input;
	t_pipex		pipe;
}	t_prompt;

typedef struct s_token_data
{
	char	*str;
	int		type; 
}	t_token_data;

enum e_token
{
	QUOTE,
	DBLQUOTE,
	PIPE,
	APP_OUT,
	HERE_DOC,
	REDIR_OUT,
	REDIR_IN,
	SPACE,
	OTHER,
};

enum e_rm_status
{
	ADD,
	DEL,
	EXT,
};


/*init data struct*/
int			init_data_struct(t_prompt *prompt);
int			init_data(t_prompt *prompt, char **env);
int			init_cmds(t_prompt *prompt);
int			init_pipex(t_pipex *pipe,t_prompt *prompt);

/* Gestion de signaux */
int			set_signal(void);

/*Manipulation de la liste chainee*/
void		data_lstdelone(t_list *cell, void (*del)(void*));
void		data_lstclear(t_list **lst, void (*del)(void*));
void		print_lst_prompt(t_prompt prompt);

/*parsing*/
int			is_only_space(char *str);
void		ft_add_history(t_prompt *prompt);
void		treating_line(t_prompt *prompt);

/*parsing tokeniser*/
int			analyse_token_prompt(t_prompt *prompt);
int			tokenizer(t_prompt *prompt, int i, const char *tok[]);
int			manage_quotes(t_prompt *prompt, int type, int i);
int			check_in_quotes(char *prompt, int *i, char c);
int			manage_pipes(t_prompt *prompt, int i);
int			manage_spaces(t_prompt *prompt, int i);
int			manage_useless_token(t_prompt *prompt, int i, const char *tok[]);
int			other_token_size(t_prompt *prompt, int i, const char *tok[]);

/*parsing cmds*/
void		add_cmds(t_prompt *prompt);
void		setup_redirs(t_token_data *cont, t_prompt *prompt, int i);
void		process_token_data(t_token_data *cont, t_prompt *prompt, int i);
void		update_cmd(t_prompt *prompt, char *strseg, char *delim, int i);
void		merge_cmd(t_prompt *prompt, char *strseg, char *delim, int i);

/*Ramasse miette alias Garbage collector*/
void		*rm_malloc(size_t size);
void		*lst_rm(void *garb, int status);
void		rm_lstclear(t_list **lst, void (*del)(void*));
void		rm_lstdelone(t_list *lst, void (*del)(void*));

/*setup erros*/
int			free_under_condition(t_prompt *prompt);
int			free_cmd_lst(t_prompt *prompt);
void		ft_free(char **av);
int			ft_error(char *error, int errnum);
 
 /*setup envirenement*/
char		**cpy_env(char *env[]);
char		*shlvl_up(char *env_prompt);
char		*checkpath_env(char *env[], char *cmd);
char		*exec_cmd(char **paths, char *cmd);
char		**get_path_env(char *env[]);


/*setup pipes*/
int			set_output_fd(t_pipex *pipe, int i);
int			set_in_out_fd(t_pipex *pipe);
int			set_cmd_exc(t_pipex *pipex, char **av, char **env);
int			set_pipe_data(char **av, t_pipex *pipex, char **env, int *i);
int			glory_pipe(t_prompt *prompt, t_pipex *pipex);

/*setup redirections*/
void		redir_fill(t_prompt *prompt, int type, char *res, int i);
int			manage_redir(t_prompt *prompt, int type, int i);
int			skype_quotes(int i, char *input);
int			ft_heredoc(t_pipex *pipe, int i);

/*split_simulator*/
char		**split_simulator(char const *str, char c);
int			count_substrim(char const *str, char c);
void		*extract_substr(char const *str, char c, char **ptr, int *i);
void		analyse_substr(const char *str, int *i, int *buf, int *space);
int			free_str_ptr(char **ptr, int j);

/*setup builtins*/
int			pre_fork_builtin(char **cmd, t_prompt *prompt);
int			is_prefork_builtin(char **cmd);
void		check_for_builtin(char **cmd, t_prompt *prompt, int i);
int			builtin_exit(char **cmd);

/*utils*/
void		*safe_malloc(size_t size);
void   		*safe_malloc_bzero(int nmemb, size_t size);
char		*strjoin_minus_arg(char *s1, char *s2);
int			exit_err(char **cmd, int err_type);
void		free_double(char **env);

/*utils cmds*/
t_list		*count_cmd(int *i, t_list *lst);

/*utils pipex*/
void	free_pipepline(t_pipex *ppx);
void	loop_free(t_pipex *pipe);
void	set_child_process(t_pipex *pipex, t_prompt *prompt, int idx);
void	close_all_fd(t_pipex *pipex);

/*utils redirections*/
void	redir_only_cmd(t_pipex *pipex, int idx);
void	redir_first_cmd(t_pipex *pipex, int idx);
void	redir_mid_cmd(t_pipex *pipex, int idx);
void	redir_last_cmd(t_pipex *pipex, int idx);
void	ft_dup(int in, int out);

# endif

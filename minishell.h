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
	int		*hd_on;
	int		*app_on;
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
	char **env;
	char **cmd;
	char *prompt;
	char *prev_input;
	t_list  *lst_input;
	t_pipex		pipe;
}	t_prompt;



/* Gestion de signaux */

/*utils*/
void *safe_malloc(size_t size);
char *strjoin_minus_arg(char *s1, char *s2);
int exit_err(char **cmd, int err_type);


/*init data struct*/
int init_data_struct(t_prompt *prompt);
int init_data(t_prompt *prompt, char **env);

/*setup envirenement*/
char	**cpy_env(char *env[]);
char	*shlvl_up(char *env_prompt);

/*utils*/
void *safe_malloc(size_t size);
char *strjoin_minus_arg(char *s1, char *s2);


/*init data struct*/
int init_data_struct(t_prompt *prompt);
int init_data(t_prompt *prompt, char **env);

/*setup envirenement*/
char	**cpy_env(char *env[]);
char	*shlvl_up(char *env_prompt);

/* Gestion de signaux */
int		set_signal(void);

/*builtin*/
int	builtin_exit(char **cmd);



# endif
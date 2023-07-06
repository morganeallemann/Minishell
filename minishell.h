/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:38:17 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 13:37:51 by inaranjo         ###   ########.fr       */
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

typedef struct s_shell_data_prompt
{
    char **env;
    char **cmd;
    char *prompt;
    char *prev_input;
    t_list  *lst_input;
    // add struct pipex
} t_prompt;

#endif


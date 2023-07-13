/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:45:12 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 14:36:18 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_data(t_prompt *prompt, char **env)
{
	g_exit_status = 0; 
	prompt->prev_input = NULL; 
	prompt->env = cpy_env(env);
	if (prompt->env == NULL)
		return (1);
	return (0);
}

int	init_data_struct(t_prompt *prompt)
{
	prompt->lst_input = NULL;
	prompt->pipe.n_cmd = 1;
	return (0);
}

/*
prompt->cmd : sotcker un tableau cmds 
prompt->pipe.limiter : stocker des informations sur les limites ou les 
restrictions liees aux commande
prompt->pipe.hd_on :  stocker des indicateurs ou des paramètres 
spécifiques aux commandes
prompt->pipe.file_in : stocker les fichiers d'entrée associés aux commandes
prompt->pipe.file_out : stocker les fichiers de sortie associés aux commandes
prompt->pipe.app_on  :  stocker des indicateurs ou des paramètres 
spécifiques aux commande
*/
int	init_cmds(t_prompt *prompt)
{
	prompt->cmd = rm_malloc(prompt->pipe.n_cmd * sizeof(char *));
	prompt->pipe.limiter = rm_malloc(prompt->pipe.n_cmd * sizeof(char *));
	prompt->pipe.here_doc = rm_malloc(prompt->pipe.n_cmd * sizeof(int));
	prompt->pipe.file_in = rm_malloc(prompt->pipe.n_cmd * sizeof(char *));
	prompt->pipe.file_out = rm_malloc(prompt->pipe.n_cmd * sizeof(char *));
	prompt->pipe.app_end = rm_malloc(prompt->pipe.n_cmd * sizeof(int));
	return (0);
}

int	init_pipex(t_pipex *pipe, t_prompt *prompt)
{
	pipe->fd = safe_malloc_bzero(pipe->n_cmd, sizeof(int *));
	pipe->pid = safe_malloc_bzero(pipe->n_cmd, sizeof(int));
	pipe->cmd = safe_malloc_bzero(pipe->n_cmd, sizeof(char **));
	pipe->path = safe_malloc_bzero(pipe->n_cmd, sizeof(char *));
	pipe->fd_hd = safe_malloc_bzero(pipe->n_cmd, sizeof(int *));
	pipe->f_in = safe_malloc_bzero(pipe->n_cmd, sizeof(int));
	pipe->f_out = safe_malloc_bzero(pipe->n_cmd, sizeof(int));
	if (set_in_out_fd(pipe) == -1)
		return (-1);
	if (set_cmd_exc(pipe, prompt->cmd, prompt->env) == -1)
		return (-1);
	return (0);
}

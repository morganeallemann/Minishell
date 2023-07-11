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

# include "minishell.h"

int init_data(t_prompt *prompt, char **env)
{ 
    //add sig status
    g_exit_status = 0; 
    prompt->prev_input = NULL; 
    prompt->env = cpy_env(env);
    if(prompt->env == NULL)
        return (1);
    return (0);
}

int init_data_struct(t_prompt *prompt)
{
    prompt->lst_input = NULL;
    //add sig status
    prompt->pipe.n_cmd = 1;
    return (0);
}



/*
prompt->cmd : sotcker un tableau cmds 
prompt->pipe.limiter : stocker des informations sur les limites ou les restrictions liees aux commande
prompt->pipe.hd_on :  stocker des indicateurs ou des paramètres spécifiques aux commandes
prompt->pipe.file_in : stocker les fichiers d'entrée associés aux commandes
prompt->pipe.file_out : stocker les fichiers de sortie associés aux commandes
prompt->pipe.app_on  :  stocker des indicateurs ou des paramètres spécifiques aux commande
*/
int	init_cmds(t_prompt *prompt)
{
	prompt->cmd = gc_malloc(prompt->pipe.n_cmd * sizeof(char *));
	prompt->pipe.limiter = gc_malloc(prompt->pipe.n_cmd * sizeof(char *));
	prompt->pipe.hd_on = gc_malloc(prompt->pipe.n_cmd * sizeof(int));
	prompt->pipe.file_in = gc_malloc(prompt->pipe.n_cmd * sizeof(char *));
	prompt->pipe.file_out = gc_malloc(prompt->pipe.n_cmd * sizeof(char *));
	prompt->pipe.app_on = gc_malloc(prompt->pipe.n_cmd * sizeof(int));
	return (0);
}


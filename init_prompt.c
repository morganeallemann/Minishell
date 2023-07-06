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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:42:21 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 15:13:24 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int main(int ac, char *av[],char *env[])
{
    t_prompt prompt;
    
    (void) av;
    if(ac != 1 || init_data(&prompt,env) == 1)
        return (1);
    while(42)
    {
        init_data_struct(&prompt);
        // add init lst_prompt
        prompt.prompt = readline("ʕ•́ᴥ•̀ʔっ");
        
    }
    return (0);

}




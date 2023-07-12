/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:45:32 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 16:07:11 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;


int	pre_fork_builtin(char **cmd, t_prompt *prompt)
{
	if (cmd[0] == NULL)
		return (0);
	if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
		g_exit_status = builtin_exit(cmd);

}



int	builtin_exit(char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1] != NULL)
	{
		printf("exit\n");
		while (cmd[1][i] != '\0')
		{
			if (!(ft_isdigit(cmd[1][i++])))
				return (exit_err(cmd, 2));
		}
		if (cmd[2] != NULL)
			return (exit_err(cmd, 1));
		exit (ft_atoi(cmd[1]));
	}
	else
	{
		printf("CIAO\n");
		exit (g_exit_status);
	}
}

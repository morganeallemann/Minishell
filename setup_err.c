/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:13:30 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 14:30:42 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_cmd_lst(t_prompt *prompt)
{
	int			i;
	t_list		*lst;

	i = 0;
	lst = prompt->lst_input;
	while (lst != NULL)
		lst = counting_cmd(&i, lst);
	data_lstclear(&prompt->lst_input, free);
	if (i != prompt->pipe.n_cmd)
		return (free_under_condition(prompt));
	return (0);
}

int	free_under_condition(t_prompt *prompt)
{
	int	i;

	i = 0;
	if (!prompt->cmd || !prompt->cmd[i])
		return (-1);
	while (i < prompt->pipe.n_cmd)
	{
		free(prompt->cmd[i]);
		if (prompt->pipe.file_in != NULL && prompt->pipe.file_in[i] != NULL)
			free(prompt->pipe.file_in[i]);
		if (prompt->pipe.file_out != NULL && prompt->pipe.file_out[i] != NULL)
			free(prompt->pipe.file_out[i]);
		if (prompt->pipe.limiter != NULL && prompt->pipe.limiter[i] != NULL)
			free(prompt->pipe.limiter[i]);
		i++;
	}
	return (-1);
}

void	ft_free(char **av)
{
	int	i;

	i = 0;
	if (av != NULL)
	{
		while (av[i])
		{
			free(av[i]);
			av[i] = NULL;
			i++;
		}
		free(av);
		av = NULL;
	}
}


int	ft_error(char *error, int errnum)
{
	perror(error);
	return (errnum);
}
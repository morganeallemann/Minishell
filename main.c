/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:42:21 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 16:03:20 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	main(int ac, char *av[], char *env[])
{
	t_prompt	prompt;

	(void) av;
	if (ac != 1 || init_data(&prompt, env) == 1)
		return (1);
	if ((set_signal()) == -1)
		return (0);
	while (42)
	{
		init_data_struct(&prompt);
		data_lstclear(&prompt.lst_input, free);
		prompt.prompt = readline(VIOLET"ʕ•́ᴥ•̀ʔっ"BLANC);
		if (prompt.prompt == NULL)
		{
			printf ("exit\n");
			free(prompt.prompt);
			free(prompt.prev_input);
			mini_lstclear(&prompt.lst_input, free);
			exit (g_exit_status);
		}
		if (prompt.prompt[0] != '\0' && is_only_space(prompt.prompt) == 1)
			treating_line(&prompt);
	}
	return (0);
}

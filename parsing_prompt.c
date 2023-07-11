/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:42:21 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 16:03:20 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	is_only_space(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	ft_add_history(t_prompt *prompt)
{
	size_t	size_input;
	char	*temp;

	size_input = ft_strlen(prompt->prompt);
	if (prompt->prev_input != NULL)
	{
		if (ft_strlen(prompt->prev_input) > ft_strlen(prompt->prompt))
			size_input = ft_strlen(prompt->prev_input);
	}
	if (prompt->prev_input == NULL || ft_strncmp(prompt->prompt,
			prompt->prev_input, size_input) != 0)
	{
		add_history(prompt->prompt);
		temp = prompt->prev_input;
		prompt->prev_input = ft_strdup(prompt->prompt);
		free(temp);
		if (prompt->prev_input == NULL)
			return ;
	}
}

void	treating_line(t_minish *minish)
{
	ft_add_history(minish);
	if (ft_token(minish) != -1)
	{
		g_exit_status = main_pipe(minish, &minish->ppx);
		mini_lstclear(&minish->lst_line, free);
	}
	else
	{
		printf("unexpected token ERROR\n");
		g_exit_status = 2;
	}
}

int	analyse_token_prompt(t_prompt *prompt)
{
	int			i;
	const char	*tok[] = {
		"\'", "\"", "|", ">>", "<<", ">", "<", " ", NULL,
	};

	i = 0;
	while (prompt->prompt[i] != '\0')
	{
		i = manage_useless_token(prompt, i, tok);
		i = tokenizer(prompt, i, tok);
		if (i == -1)
		{
			data_lstclear(&prompt->lst_input, free);
			return (-1);
		}
		if (prompt->prompt[i] != '\0')
			i++;
	}
	add_cmds(prompt);
	return (ft_err_handling(prompt));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:42:21 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 16:03:20 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	add_cmds(t_prompt *prompt)
{
	t_list		*lst;
	t_token_data	*cont;
	int			i;

	lst = prompt->lst_input;
	init_cmds(prompt);
	i = 0;
	while (lst != NULL)
	{
		cont = lst->content;
		process_token_data(cont, prompt, i);
		if (cont->type >= APP_OUT && cont->type <= REDIR_IN)
		{
			if (ft_strncmp(cont->str, "", 1) != 0)
				setup_redirs(cont, prompt, i);
			else
				cont->str = NULL;
		}
		else if (cont->type == PIPE && prompt->cmd[i] != NULL)
			i++;
		lst = lst->next;
	}
}

void	setup_redirs(t_token_data *cont, t_prompt *prompt, int i)
{
	char		*tmp;

	tmp = ft_strdup(cont->str);
	free(cont->str);
	redir_fill(prompt, cont->type, tmp, i);
	cont->str = ft_strdup("");
	update_cmd(prompt, cont->str, NULL, i);
}

void	process_token_data(t_token_data *cont, t_prompt *prompt, int i)
{
	if (cont->type == OTHER)
	{
		cont->str = expand_var(cont->str, prompt);
		update_cmd(prompt, cont->str, NULL, i);
	}
	else if (cont->type == QUOTE)
	{
		cont->str = expand_var(cont->str, prompt);
		update_cmd(prompt, cont->str, "'", i);
	}
	else if (cont->type == DBLQUOTE)
	{
		cont->str = expand_var(cont->str, prompt);
		update_cmd(prompt, cont->str, "\"", i);
	}
	else if (cont->type == SPACE)
		update_cmd(prompt, cont->str, NULL, i);
}

void	update_cmd(t_prompt *prompt, char *strseg, char *delim, int i)
{
	if (prompt->cmd[i] == NULL)
	{
		if (delim == NULL)
		{
			if (is_only_space(strseg) == 0)
				prompt->cmd[i] = ft_strdup(" ");
			else
				prompt->cmd[i] = ft_strdup(strseg);
		}
		else
			prompt->cmd[i] = ft_strtrim(strseg, delim);
	}
	else
		merge_cmd(prompt, strseg, delim, i);
}

void	merge_cmd(t_prompt *prompt, char *strseg, char *delim, int i)
{
	char	*tmp;

	if (delim == NULL)
	{
		if (is_only_space(strseg) == 0)
			prompt->cmd[i] = strjoin_minus_arg(prompt->cmd[i], " ");
		else
			prompt->cmd[i] = strjoin_minus_arg(prompt->cmd[i], strseg);
	}
	else
	{
		tmp = ft_strtrim(strseg, delim);
		prompt->cmd[i] = strjoin_minus_arg(prompt->cmd[i], tmp);
		free(tmp);
	}
}
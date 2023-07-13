/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:42:21 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 16:03:20 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenizer(t_prompt *prompt, int i, const char *tok[])
{
	int	j;

	j = 0;
	while (tok[j] != NULL)
	{
		if (ft_strncmp(&prompt->prompt[i], tok[j], ft_strlen(tok[j])) == 0)
		{
			if (j == 0 || j == 1)
				return (manage_quotes(prompt, j, i));
			else if (j == 2)
				return (manage_pipes(prompt, i));
			else if (j == 7)
				return (manage_spaces(prompt, i));
			else
				return (manage_redir(prompt, j, i));
		}
		j++;
	}
	return (i);
}

/*init,alloue,define le type,check,ajoute 
line = "Hello, 'World!'"
j = i = 7 
cell->type = 1 (DBLQUOTE)
cell->type = 0 (QUOTE)
cell->str 0= 'World!'*/
int	manage_quotes(t_prompt *prompt, int type, int i)
{
	int				j;
	char			c;
	char			*line;
	t_token_data	*cell;

	cell = safe_malloc(sizeof(struct s_token_data));
	line = prompt->prompt;
	j = i;
	c = '"';
	cell->type = DBLQUOTE;
	if (type == 0)
	{
		cell->type = QUOTE;
		c = '\'';
	}
	if (check_in_quotes(line, &i, c) == -1)
	{
		free (cell);
		return (-1);
	}
	cell->str = ft_substr(&line[j], 0, (i + 1) - j);
	ft_lstadd_back(&prompt->lst_input, ft_lstnew(cell));
	return (i);
}

/*Vérification si les guillemets sont correctement fermés dans la chaîne*/
int	check_in_quotes(char *prompt, int *i, char c)
{
	(*i)++;
	while (prompt[*i] != c)
	{
		if (prompt[*i] == '\0')
			return (-1);
		(*i)++;
	}
	return (0);
}

/*init,alloc,count pipe cmd, split, define, add to lst
prompt->prompt = "ls | grep main"
prompt->pipe.n_cmd = 1
cell->str = ls
cell->type = enum 2 (PIPE)
*/
int	manage_pipes(t_prompt *prompt, int i)
{
	int				j;
	char			*line;
	t_token_data	*cell;

	cell = safe_malloc(sizeof(struct s_token_data));
	line = prompt->prompt;
	j = i;
	prompt->pipe.n_cmd++;
	cell->str = ft_substr(&line[j], 0, (i + 1) - j);
	cell->type = PIPE;
	ft_lstadd_back(&prompt->lst_input, ft_lstnew(cell));
	return (i);
}

int	manage_spaces(t_prompt *prompt, int i)
{
	int				j;
	char			*line;
	t_token_data	*cell;

	cell = safe_malloc(sizeof(struct s_token_data));
	line = prompt->prompt;
	j = i;
	cell->str = ft_substr(&line[j], 0, (i + 1) - j);
	cell->type = ESPACE;
	ft_lstadd_back(&prompt->lst_input, ft_lstnew(cell));
	return (i);
}

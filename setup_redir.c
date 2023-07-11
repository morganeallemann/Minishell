/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:42:21 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 16:03:20 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    redir_fill(t_prompt *prompt, int type, char *res, int i)
{
	if (type == APP_OUT || type == REDIR_OUT)
	{
		update_ptr(prompt->pipe.file_out, i, res);
		if (type == APP_OUT)
			prompt->pipe.app_on[i] = 1;
	}
	else if (type == HERE_DOC)
	{
		prompt->pipe.hd_on[i] = 1;
		update_ptr(prompt->pipe.limiter, i, res);
	}
	else
		update_ptr(prompt->pipe.file_in, i, res);
}

void    update_ptr(char **ptr, int i, char *res)
{
	if (ptr[i] == NULL)
		ptr[i] = res;
	else
	{
		free(ptr[i]);
		ptr[i] = res;
	}
}

int manage_redir(t_prompt *prompt, int type, int i)
{
	int			j;
	char		*input;
	t_token_data	*cell;

	cell = safe_malloc(sizeof(struct s_token_data));
	input = prompt->prompt;
	cell->type = type;
	while (input[i] == ' ' || input[i] == '<' || input[i] == '>')
		i++;
	j = i;
	if (input[i] == '\'' || input[i] == '"')
		j++;
	i = skype_quotes(i, input);
	if (i == -1)
	{
		free(cell);
		return (-1);
	}
	cell->str = ft_substr(&input[j], 0, i - j);
	ft_lstadd_back(&prompt->lst_input, ft_lstnew(cell));
	return (i);
}

int skype_quotes(int i, char *input)
{
	if (input[i] == '\'')
	{
		i++;
		while (input[i] != '\'')
		{
			if (input[i++] == '\0')
				return (-1);
		}
	}
	else if (input[i] == '"')
	{
		i++;
		while (input[i] != '"')
		{
			if (input[i++] == '\0')
				return (-1);
		}
	}
	else
	{
		while (input[i] != '\0' && input[i] != ' ')
			i++;
	}
	return (i);
}

/*REVOIR BESOIN DES SIG*/
int	ft_heredoc(t_pipex *pipe, int i)
{
	char	*input;
	size_t	limit_len;

	//ft_signals_n_attr(HD);
	limit_len = ft_strlen(pipe->limiter[i]);
	write(1, "> ", 2);
	input = get_next_line(0);
	if (!input && g_exit_status != 130)
		write(1, "\n", 1);
	while (g_exit_status != 130 && input
		&& ft_strncmp(input, pipe->limiter[i], limit_len) != 0)
	{
		write(1, "> ", 2);
		write(pipe->fd_hd[i][1], input, ft_strlen(input));
		free(input);
		input = get_next_line(0);
		if (!input && g_exit_status != 130)
			write(1, "\n", 1);
	}
	//ft_signals_n_attr(RESET);
	free(input);
	close(pipe->fd_hd[i][1]);
	return (0);
}

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

int	set_output_fd(t_pipex *pipe, int i)
{
	int	output_fd;

	if (pipe->app_end[i] == 0)
		output_fd = open(pipe->file_out[i], O_CREAT | O_WRONLY | O_TRUNC, 00644);
	else
		output_fd = open(pipe->file_out[i], O_CREAT | O_APPEND | O_WRONLY, 00644);
	return (output_fd);
}

int	set_in_out_fd(t_pipex *pipe)
{
	int	i;

	i = 0;
	while (i < pipe->n_cmd)
	{
		if (pipe->file_in[i] == NULL)
			pipe->f_in[i] = 0;
		if (pipe->file_out[i] == NULL)
			pipe->f_out[i] = 1;
		if (pipe->file_out[i] != NULL)
		{
			pipe->f_out[i] = set_output_fd(pipe, i);
			if (pipe->f_out[i] == -1)
				return (ft_error(pipe->file_out[i], -1));
		}
		if (pipe->here_doc[i] == 0 && pipe->file_in[i] != NULL)
		{
			pipe->f_in[i] = open(pipe->file_in[i], O_RDONLY);
			if (pipe->f_in[i] == -1)
				return (ft_error(pipe->file_in[i], -1));
		}
		i++;
	}
	return (0);
}

int	set_cmd_exc(t_pipex *pipex, char **av, char **env)
{
	int	i;
	int	input;

	i = 0;
	while (i < pipex->n_cmd)
	{
		if (pipex->here_doc[i] == 1)
		{
			pipex->fd_hd[i] = safe_malloc_bzero(2, sizeof(int));
			if (pipe(pipex->fd_hd[i]) == -1)
				ft_error(av[0], -3);
			if (ft_heredoc(pipe, i) == -1)
				return (ft_error(av[0], -1));
		}
		pipex->cmd[i] = split_simulator(av[i], ' ');
		if (pipex->cmd[i] == NULL)
			return (ft_error(av[0], -1));
		input = set_pipe_data(av, pipe, env, &i);
		if (input != 0)
			return (input);
	}
	return (0);
}

int	set_pipe_data(char **av, t_pipex *pipex, char **env, int *i)
{
	free(av[*i]);
	pipex->path[*i] = checkpath_env(env, pipex->cmd[*i][0]);
	pipex->fd[*i] = safe_malloc_bzero(2, sizeof(int));
	if (pipe(pipex->fd[*i]) == -1)
		return (ft_error(av[0], -3));
	(*i)++;
	return (0);
}


int	main_pipe(t_prompt *prompt, t_pipex *pipex)
{
	int		i;
	int		init_status;

	i = 0;
	init_status = init_pipex(pipex, prompt);
	if (init_status < 0)
	{
		if (init_status == -1)
			free_pipepline(pipex);
		return (1);
	}
	while (i < pipex->n_cmd)
	{
		if (pre_fork_builtin(pipex->cmd[i], prompt) == 0)
			set_child_process(pipex, prompt, i);
		i++;
	}
	return (set_waitpid_status(pipex));
}
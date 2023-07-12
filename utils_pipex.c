/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:42:21 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 16:03:20 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void loop_free(t_pipex *pipe)
{
	int i;

	i = 0;
	while (i < pipe->n_cmd)
	{
		ft_free(pipe->cmd[i]);
		pipe->cmd[i] = NULL;
		free(pipe->path[i]);
		pipe->path[i] = NULL;
		free(pipe->fd[i]);
		pipe->fd[i] = NULL;
		free(pipe->fd_hd[i]);
		pipe->fd_hd[i] = NULL;
		free(pipe->file_in[i]);
		pipe->file_in[i] = NULL;
		free(pipe->file_out[i]);
		pipe->file_out[i] = NULL;
		free(pipe->limiter[i]);
		pipe->limiter[i] = NULL;
		i++;
	}
}

void	free_pipepline(t_pipex *pipe)
{
	loop_free(pipe);
	if (pipe->cmd != NULL)
		free(pipe->cmd);
	if (pipe->path != NULL)
		free(pipe->path);
	if (pipe->pid != NULL)
		free(pipe->pid);
	if (pipe->fd != NULL)
		free(pipe->fd);
	if (pipe->f_in != NULL)
		free(pipe->f_in);
	if (pipe->f_out != NULL)
		free(pipe->f_out);
	if (pipe->fd_hd != NULL)
		free(pipe->fd_hd);
}

void	set_child_process(t_pipex *pipex, t_prompt *prompt, int idx)
{
	//ft_signals_n_attr(NO_REPROMPT);
	pipex->pid[idx] = fork();
	if (pipex->pid[idx] < 0)
		exit(1);
	if (pipex->pid[idx] == 0)
	{
		if (pipex->n_cmd == 1)
			redir_only_cmd(pipex, idx);
		else if (idx == 0)
			redir_first_cmd(pipex, idx);
		else if (idx == pipex->n_cmd - 1)
			redir_last_cmd(pipex, idx);
		else
			redir_mid_cmd(pipex, idx);
		close_all_fd(pipex);
		//§ft_signals_n_attr(UNSET);
		check_for_builtin(pipex->cmd[idx], prompt, idx);
		execve(pipex->path[idx], pipex->cmd[idx], prompt->env);
		perror(pipex->cmd[idx][0]);
		if (errno == ENOENT || pipex->cmd[idx][0] == NULL)
			exit(127);
		exit(126);
	}
	return ;
}

void	close_all_fd(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->n_cmd)
	{
		close(pipex->fd[i][0]);
		close(pipex->fd[i][1]);
		if (pipex->file_in[i] != NULL)
			close(pipex->f_in[i]);
		if (pipex->file_out[i] != NULL)
			close(pipex->f_out[i]);
		if (pipex->here_doc[i] == 1)
			close(pipex->fd_hd[i][0]);
		i++;
	}
}

int	set_waitpid_status(t_pipex *pipex)
{
	int	i;
	int	wstatus;
	int	status;

	i = 0;
	status = 0;
	while (i < pipex->n_cmd)
	{
		close_all_fd(pipex);
		waitpid(pipex->pid[i], &wstatus, 0);
		if ((pipex->cmd[i][0] != NULL && is_prefork_builtin(pipex->cmd[i]) == 0)
			|| (g_exit_status == 131 || g_exit_status == 130))
			status = g_exit_status;
		if (WIFEXITED(wstatus))
			status = WEXITSTATUS(wstatus);
		i++;
	}
	free_pipepline(pipex);
	return (status);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:45:32 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 16:07:11 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_only_cmd(t_pipex *pipex, int idx)
{
	if (pipex->here_doc[idx] == 0)
		ft_dup(pipex->f_in[idx], pipex->f_out[idx]);
	else
		ft_dup(pipex->fd_hd[idx][0], pipex->f_out[idx]);
}

void	redir_first_cmd(t_pipex *pipex, int idx)
{
	if (pipex->here_doc[idx] == 0)
	{
		if (pipex->file_out[idx] == NULL)
			ft_dup(pipex->f_in[idx], pipex->fd[idx][1]);
		else
			ft_dup(pipex->f_in[idx], pipex->f_out[idx]);
	}
	else
	{
		if (pipex->file_out[idx] == NULL)
			ft_dup(pipex->fd_hd[idx][0], pipex->fd[idx][1]);
		else
			ft_dup(pipex->fd_hd[idx][0], pipex->f_out[idx]);
	}
}

void	redir_mid_cmd(t_pipex *pipex, int idx)
{
	if (pipex->here_doc[idx] == 0)
	{
		if (pipex->file_in[idx] == NULL)
		{
			if (pipex->file_out[idx] == NULL)
				ft_dup(pipex->fd[idx - 1][0], pipex->fd[idx][1]);
			else
				ft_dup(pipex->fd[idx - 1][0], pipex->f_out[idx]);
		}
		else
		{
			if (pipex->file_out[idx] == NULL)
				ft_dup(pipex->f_in[idx], pipex->fd[idx][1]);
			else
				ft_dup(pipex->f_in[idx], pipex->f_out[idx]);
		}
	}
	else
	{
		if (pipex->file_out[idx] == NULL)
			ft_dup(pipex->fd_hd[idx][0], pipex->fd[idx][1]);
		else
			ft_dup(pipex->fd_hd[idx][0], pipex->f_out[idx]);
	}
}

void	redir_last_cmd(t_pipex *pipex, int idx)
{
	if (pipex->here_doc[idx] == 0)
	{
		if (pipex->file_in[idx] == NULL)
			ft_dup(pipex->fd[idx - 1][0], pipex->f_out[idx]);
		else
			ft_dup(pipex->f_in[idx], pipex->f_out[idx]);
	}
	else
		ft_dup(pipex->fd_hd[idx][0], pipex->f_out[idx]);
}

void	ft_dup(int in, int out)
{
	if (dup2(in, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(out, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
}

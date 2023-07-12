/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:13:30 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 14:30:42 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cpy_env(char *env[])
{
	int			i;
	static int	flag;
	char		**cpy_env;

	i = 0;
	while (env[i])
		i++;
	cpy_env = safe_malloc((i + 2) * sizeof(char *));
	if (cpy_env == NULL)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0 && flag == 0)
		{
			cpy_env[i] = shlvl_up(env[i]);
			flag = 1;
		}
		else
			cpy_env[i] = ft_strdup(env[i]);
	}
	if (flag != 1)
		cpy_env[i++] = ft_strdup("SHLVL=1");
	cpy_env[i] = NULL;
	return (cpy_env);
}

char	*shlvl_up(char *env_prompt)
{
	int		i;
	int		value;
	char	*alpha_value;
	char	*result;

	i = 0;
	while (env_prompt[i] != '\0' && (!ft_isdigit(env_prompt[i])))
		i++;
	if (env_prompt[i] == '\0')
		value = 0 + 1;
	else
		value = ft_atoi(&env_prompt[i]) + 1;
	result = ft_substr(env_prompt, 0, i);
	alpha_value = ft_itoa(value);
	result = strjoin_minus_arg(result, alpha_value);
	free(alpha_value);
	return (result);
}

char	*checkpath_env(char *env[], char *cmd)
{
	char	**paths;
	char	*fullpath;
	char	*cmd_cpy;

	if (!cmd)
		cmd = "";
	if (ft_strchr(cmd, '/'))
	{
		cmd_cpy = ft_strdup(cmd);
		return (cmd_cpy);
	}
	paths = get_path_env(env);
	fullpath = exec_cmd(paths, cmd);
	ft_free(paths);
	return (fullpath);
}

char	*exec_cmd(char **paths, char *cmd)
{
	int		i;
	char	*newpath;
	char	*fullpath;

	i = 0;
	while (paths[i])
	{
		newpath = ft_strjoin(paths[i], "/");
		if (!newpath)
			exit(1);
		fullpath = ft_strjoin(newpath, cmd);
		if (access(fullpath, F_OK) == 0 && access(fullpath, X_OK) == 0)
		{
			free(newpath);
			return (fullpath);
		}
		free(newpath);
		free(fullpath);
		i++;
	}
	newpath = ft_strjoin(paths[0], "/");
	fullpath = ft_strjoin(newpath, cmd);
	free(newpath);
	return (fullpath);
}

char	**get_path_env(char *env[])
{
	int		i;
	char	*defpath;
	char	**paths;
	char	*envline;

	i = 0;
	paths = NULL;
	defpath = "/";
	while (env[i])
	{
		envline = ft_strnstr(env[i], "PATH=", 5);
		if (envline != NULL)
			paths = ft_split(&envline[5], ':');
		i++;
	}
	if (paths == NULL)
		paths = ft_split(defpath, ':');
	return (paths);
}

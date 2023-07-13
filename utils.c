/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:20:14 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 15:49:48 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*safe_malloc(size_t size)
{
	void	*node;

	node = malloc(size);
	if (node == NULL)
	{
		printf("Memory allocation failed !!\n");
		exit(10);
	}
	return (node);
}

void	*safe_malloc_bzero(int nmemb, size_t size)
{
	void	*node;

	node = ft_calloc(nmemb, size);
	if (node == NULL)
	{
		printf("Memory allocation failed !!\n");
		exit(10);
	}
	return (node);
}

char	*strjoin_minus_arg(char *s1, char *s2)
{
	void	*temp;
	int		i;

	i = 0;
	while (s1[i])
	{
		i++;
	}
	s1[i] = ' ';
	s1[++i] = '\0';
	temp = ft_strjoin(s1, s2);
	free(s1);
	return (temp);
}

int	exit_err(char **cmd, int err_type)
{
	if (err_type == 1)
	{
		printf("%s: too many arguments\n", cmd[0]);
		exit (1);
	}
	else if (err_type == 2)
	{
		printf("%s: numeric argument required\n", cmd[1]);
		exit (255);
	}
	return (0);
}

void	free_double(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		free(env[i++]);
	free (env);
}

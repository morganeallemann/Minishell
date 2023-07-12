/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_simulator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:42:21 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 16:03:20 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	**split_simulator(char const *str, char c)
{
	char	**ptr;
	int		j;
	int		i[1];

	i[0] = 0;
	ptr = safe_malloc((count_substrim(str, c) + 1) * sizeof(ptr));
	if (ptr == NULL)
		return (NULL);
	j = 0;
	while (j < (count_substrim(str, c)))
	{
		if (extract_substr(str, c, &(ptr[j]), i) == NULL)
			if (free_str_ptr(ptr, j) == 0)
				return (NULL);
		j++;
	}
	ptr[j] = NULL;
	return (ptr);
}

int	count_substrim(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while ((str[i] == c && i == 0) || (str[i] == c && str[i - 1] != '\\'))
			i++;
		while (str[i] != c && str[i] != '\0')
		{
			if (str[i] == '\\' && str[i + 1] == c)
				i++;
			i++;
		}
		if (str[i - 1] != c || (str[i - 1] == c && str[i - 2] == '\\'))
		{
			count++;
			if (str[i] != '\0')
				i++;
		}
	}
	return (count);
}

void	*extract_substr(char const *str, char c, char **ptr, int *i)
{
	int	idx;
	int	buf;
	int	space;

	buf = 0;
	space = 0;
	analyse_substr(str, i, &buf, &space);
	*ptr = safe_malloc((buf + 1) * sizeof(char));
	if (*ptr == NULL)
		return (NULL);
	i[0] -= buf + space;
	idx = 0;
	while (str[i[0]] != c && str[i[0]] != '\0')
	{
		if (str[i[0]] == '\\' && str[i[0] + 1] == c)
			i[0]++;
		(*ptr)[idx++] = str[i[0]++];
	}
	(*ptr)[idx] = '\0';
	return (*ptr);
}

void	analyse_substr(const char *str, int *i, int *buf, int *space)
{
	char	c;

	c = ' ';
	while ((str[i[0]] == c && i[0] == 0)
		|| (str[i[0]] == c && str[i[0] - 1] != '\\'))
		i[0]++;
	while (str[i[0]] != c && str[i[0]] != '\0' && (*buf)++ != -1)
	{
		if (str[i[0]] == '\\' && str[i[0]++ + 1] == c)
			(*space)++;
		i[0]++;
	}
}

int	free_str_ptr(char **ptr, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free (ptr[i]);
		i++;
	}
	free(ptr);
	return (0);
}
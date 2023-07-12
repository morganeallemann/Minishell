/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:42:21 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 16:03:20 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	check_var_end(char *quote, int j)
{
	if ((ft_isdigit(quote[j - 1])
			|| quote[j - 1] == '?') && quote[j - 2] == '$')
		return (0);
	if (quote[j] != ' ' && quote[j] != '\"' && quote[j] != '\0'
		&& quote[j] != '$' && quote[j] != '\'')
		return (1);
	return (0);
}

char	*itoa_exit_status(char *var)
{
	char	*temp;

	temp = var;
	var = ft_itoa(g_exit_status);
	free(temp);
	return (var);
}


int	escaped_str_size(char *input)
{
	int		j;
	int		escaped_size;

	j = 0;
	escaped_size = 0;
	while (input[j] != '\0')
	{
		if (input[j++] == ' ')
			escaped_size += 2;
		else
			escaped_size++;
	}
	return (escaped_size);
}
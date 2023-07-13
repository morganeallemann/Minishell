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

void	size_dol_or_var(char *var, int *size, t_prompt *prompt)
{
	char	*temp;
	char	*val;

	if (ft_strncmp(var, "?", 2) == 0)
	{
		temp = ft_itoa(g_exit_status);
		*size += ft_strlen(temp);
		free(var);
		free(temp);
	}
	else
	{	
		temp = strjoin_minus_arg(var, "=");
		val = check_env_var(prompt->env, temp);
		if (val != NULL)
		{
			*size += ft_strlen(val);
			free(val);
		}
	}
}

int	new_size(char *quote, t_prompt *prompt)
{
	int		i;
	int		j;
	int		tot_size;
	char	*var;

	j = 0;
	tot_size = 0;
	var = NULL;
	while (quote[j] != '\0')
	{
		if (quote[j++] == '$' && quote[0] != '\'')
		{
			i = j;
			while (check_var_end(quote, j))
				j++;
			var = ft_substr(&quote[i], 0, j - (i));
			size_dol_or_var(var, &tot_size, prompt);
		}
		else
			tot_size++;
	}
	return (tot_size);
}
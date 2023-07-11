/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:42:21 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 16:03:20 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*expand_variables(char *quote, t_prompt *prompt)
{
	int		j;
	char	*ret;

	j = 0;
	ret = safe_malloc_bzero(new_size(quote, prompt) + 1, sizeof(char));
	while (quote[j] != '\0')
	{
		if (quote[j] == '$' && quote[0] != '\'')
			treating_expand(quote, prompt, &j, ret);
		else
			ret[ft_strlen(ret)] = quote[j++];
	}
	free(quote);
	ret = escape_spaces(ret);
	return (ret);
}

void	treating_expand(char *quote, t_prompt *prompt, int *j, char *ret)
{
	int		i[2];
	char	*var;

	i[0] = 0;
	(*j)++;
	i[0] = *j;
	while (is_dol_end(quote, *j))
		(*j)++;
	var = find_var(prompt, quote, i, j);
	i[0] = 0;
	if (var != NULL)
	{
		while (var[i[0]] != '\0')
		{
			ret[ft_strlen(ret)] = var[i[0]++];
			(*j)++;
		}
		free(var);
	}
	*j = (*j - i[0]) + i[1];
}

char	*find_var(t_prompt *prompt, char *quote, int i[2], int *j)
{
	char	*var;
	char	*tmp;

	i[1] = 0;
	var = ft_substr(&quote[i[0]], 0, *j - i[0]);
	i[1] = ft_strlen(var) + 1;
	if (ft_strncmp(var, "?", 2) == 0)
		var = w_itoa_rm(var);// to check
	else
	{
		tmp = strjoin_minus_arg(var, "=");
		var = check_env_var(prompt->env, tmp);
	}
	*j = i[0] - 1;
	return (var);
}

char	*check_env_var(char **env, char *var)
{
	int		i;	
	char	*env_input;
	char	*temp;

	i = 0;
	env_input= NULL;
	while (env[i] != NULL)
	{
		env_input = ft_strnstr(env[i], var, ft_strlen(var));
		if (env_input != NULL)
		{
			temp = ft_strdup(&env_input[ft_strlen(var)]);
			free(var);
			return (temp);
		}
		i++;
	}
	free(var);
	return (NULL);
}

char	*escape_spaces(char *ret)
{
	int		i;
	int		j;
	char	*newret;

	j = 0;
	i = 0;
	newret = safe_malloc_bzero((escaped_size(ret) + 1), sizeof(char));
	if (newret == NULL)
		return (NULL);
	while (ret[j] != '\0')
	{
		if (ret[j] == ' ')
			newret[i++] = '\\';
		newret[i++] = ret[j++];
	}
	newret[i] = '\0';
	free (ret);
	return (newret);
}
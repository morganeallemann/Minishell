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

char	*expand_var(char *input, t_prompt *prompt)
{
	int		j;
	char	*res;

	j = 0;
	res = safe_malloc_bzero(new_size(input, prompt) + 1, sizeof(char));
	while (input[j] != '\0')
	{
		if (input[j] == '$' && input[0] != '\'')
			expand_var_and_cpy(input, prompt, &j, res);
		else
			res[ft_strlen(res)] = input[j++];
	}
	free(input);
	res= sanitize_spaces(res);
	return (res);
}

void	expand_var_and_cpy(char *input, t_prompt *prompt, int *j, char *ret)
{
	int		i[2];
	char	*var;

	i[0] = 0;
	(*j)++;
	i[0] = *j;
	while (check_var_end(input, *j))
		(*j)++;
	var = search_var(prompt, input, i, j);
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

char	*search_var(t_prompt *prompt, char *input, int i[2], int *j)
{
	char	*var;
	char	*tmp;

	i[1] = 0;
	var = ft_substr(&input[i[0]], 0, *j - i[0]);
	i[1] = ft_strlen(var) + 1;
	if (ft_strncmp(var, "?", 2) == 0)
		var = itoa_exit_status(var);
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

char	*sanitize_spaces(char *ret)
{
	int		i;
	int		j;
	char	*newres;

	j = 0;
	i = 0;
	newres = safe_malloc_bzero((escaped_str_size(ret) + 1), sizeof(char));
	if (newres == NULL)
		return (NULL);
	while (ret[j] != '\0')
	{
		if (ret[j] == ' ')
			newres[i++] = '\\';
		newres[i++] = ret[j++];
	}
	newres[i] = '\0';
	free (ret);
	return (newres);
}

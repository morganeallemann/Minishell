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

# include "minishell.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useless_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:42:21 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 16:03:20 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_useless_token(t_prompt *prompt, int i, const char *tok[])
{
	int			size;
	char		*str;
	t_token_data	*cell;

	cell = safe_malloc(sizeof(t_token_data));
	size = other_token_size(prompt, i, tok);
	if (size > 0)
	{
		str = ft_substr(&prompt->prompt[i], 0, size);
		if (is_only_space(str) == 1)
		{
			cell->str = ft_strtrim(str, " ");
			cell->type = OTHER;
			ft_lstadd_back(&prompt->lst_input, ft_lstnew(cell));
		}
		free(str);
	}
	else
		free(cell);
	return (i + size);
}



/*Vérifie si le caractère actuel correspond à un token en utilisant ft_strncmp
Retourne la taille finale de la sous-chaîne non tokenable
*/
int	other_token_size(t_prompt *prompt, int i, const char *tok[])
{
	int		size;
	int		j;

	size = 0;
	while (prompt->prompt[i] != '\0')
	{
		j = 0;
		while (tok[j] != NULL)
		{
			if (ft_strncmp(&prompt->prompt[i], tok[j], ft_strlen(tok[j])) == 0)
			{
				return (size);
			}
			else
				j++;
		}
		if (tok[j] == NULL || j == OTHER)
		{
			size++;
			i++;
		}
	}
	return (size);
}



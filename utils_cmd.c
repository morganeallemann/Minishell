/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:13:30 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 14:30:42 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*count_cmd(int *i, t_list *lst)
{
	t_token_data	*cont;

	cont = lst->content;
	if (cont->type != SPACE && cont->type != PIPE)
	{
		while (cont->type != PIPE)
		{
			if (cont->type >= APP_OUT && cont->type <= REDIR_IN
				&& cont->str == NULL)
				(*i)--;
			lst = lst->next;
			if (lst == NULL)
				break ;
			cont = lst->content;
		}
		(*i)++;
	}
	if (lst != NULL)
		lst = lst->next;
	return (lst);
}

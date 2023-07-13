/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:38:17 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 16:03:00 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Delete seulement un noeud/cell cible*/
void	data_lstdelone(t_list *cell, void (*del)(void*))
{
	t_token_data	*content;

	content = cell->content;
	if (cell && del)
	{
		del(content->str);
		del(content);
		free(cell);
	}
}

/*delete la totalite de la liste*/
void	data_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	temp = *lst;
	if (*lst && del)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			data_lstdelone(*lst, del);
			*lst = temp;
		}
	}
}

/*imprime la list pour debug*/
void	print_lst_prompt(t_prompt prompt)
{
	t_list			*lst;
	t_token_data	*cont;

	lst = prompt.lst_input;
	while (lst != NULL)
	{
		cont = lst->content;
		printf("%s\n", cont->str);
		printf("%d\n", cont->type);
		lst = lst->next;
	}
}

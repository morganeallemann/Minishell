/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ramasse_miette.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:42:21 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 16:03:20 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void *rm_malloc(size_t size)
{
    void *rm; 

    rm = safe_malloc_bzero(1, size);
	lst_rm(rm,ADD);
	return(rm);

}

void	*lst_rm(void *garb, int status)
{
	static t_list	*rm_list;

	if (status == ADD)
		ft_lstadd_front(&rm_list, ft_lstnew(garb));
	else
		rm_lstclear(&rm_list, free);
	return (NULL);
}

void	rm_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	temp = *lst;
	if (*lst && del)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			rm_lstdelone(*lst, del);
			*lst = temp;
		}
	}
}

void	rm_lstdelone(t_list *lst, void (*del)(void*))
{
	void	*node;

	node = lst->content;
	if (lst && del && node)
	{
		del(node);
		free(lst);
	}
}


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

<<<<<<< HEAD
# include "minishell.h"

void rm_malloc(size_t size)
=======
#include "minishell.h"

void	rm_malloc(size_t size)
>>>>>>> 13e5920b3c2ac1c6f9376d6a6ddcf782d7bfd7ad
{
    void *rm; 

    rm = safe_malloc(sizeof(char *));
<<<<<<< HEAD
	lst_rm(rm,ADD);
	return(rm);

=======
>>>>>>> 13e5920b3c2ac1c6f9376d6a6ddcf782d7bfd7ad
}

void	*lst_rm(void *garb, int status)
{
	static t_list	*rm_list;

	if (status == ADD)
		ft_lstadd_front(&rm_list, ft_lstnew(garb));
	else
		gc_lstclear(&rm_list, free);
	return (NULL);
}
<<<<<<< HEAD

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
=======
>>>>>>> 13e5920b3c2ac1c6f9376d6a6ddcf782d7bfd7ad

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

#include "minishell.h"

void	rm_malloc(size_t size)
{
    void *rm; 

    rm = safe_malloc(sizeof(char *));
}

void	*gc_malloc(size_t size)
{
	void	*garb;

	garb = w_ft_calloc_prot(1, size);
	ft_gc(garb, ADD);
	return (garb);
}

void	*ft_gc(void *garb, int status)
{
	static t_list	*gc_list;

	if (status == ADD)
		ft_lstadd_front(&gc_list, ft_lstnew(garb));
	else
		gc_lstclear(&gc_list, free);
	return (NULL);
}

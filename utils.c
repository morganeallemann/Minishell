/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:20:14 by inaranjo          #+#    #+#             */
/*   Updated: 2023/07/06 14:28:25 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


void *safe_malloc(size_t size)
{
    void *node;

    node = malloc(size);
    if (node == NULL)
    {
        printf("Memory allocation failed !!\n");
        exit(10);
    }
    return node;
}

char *strjoin_minus_arg(char *s1, char *s2)
{
    void *temp;

    temp = ft_strjoin(s1, s2);
    free(s1);
    return (temp);
}

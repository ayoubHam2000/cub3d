/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:55:11 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/29 13:10:06 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	free_all(void *p)
{
	t_add_node	*node;
	t_add_node	*tmp;
	t_add_node	*list;

	ft_addrs_exclude(p);
	list = add_address(NULL, 1);
	node = list;
	while (node)
	{
		free(node->p);
		tmp = node->next;
		free(node);
		node = tmp;
	}
	add_address(NULL, 2);
}

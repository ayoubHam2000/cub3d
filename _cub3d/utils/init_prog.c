/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:00:50 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/28 19:01:06 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_prog	*init_prog(void)
{
	t_prog	*prog;

	prog = malloc(sizeof(t_prog));
	if (!prog)
		return (NULL);
	prog->w_size = WIN_SIZE;
	prog->map = NULL;
	return (prog);
}

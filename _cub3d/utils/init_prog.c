/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:00:50 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/30 11:40:38 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_prog	*init_prog(void)
{
	t_prog	*prog;

	prog = ft_malloc(sizeof(t_prog));
	prog->w_size = WIN_SIZE;
	prog->map = NULL;
	prog->img.img = NULL;
	prog->img.addr = NULL;
	prog->player.angle = 0;
	prog->player.x = 0;
	prog->player.y = 0;
	prog->player.speed = 1;
	return (prog);
}

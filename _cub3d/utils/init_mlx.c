/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbel-bas <mbel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:01:18 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/24 14:59:45 by mbel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*init_mlx(t_prog *prog)
{
	prog->mlx = mlx_init();
	prog->win = mlx_new_window(prog->mlx, WIDTH * 2, HEIGHT, WIN_TITLE);
	if (!prog->mlx || !prog->win)
		return (NULL);
	return (prog);
}

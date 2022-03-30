/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:01:18 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/29 22:22:19 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*init_mlx(t_prog *prog)
{
	prog->mlx = mlx_init();
	prog->win = mlx_new_window(prog->mlx, prog->w_size, prog->w_size, WIN_TITLE);
	if (!prog->mlx || !prog->win)
		return (NULL);
	prog->img.img = NULL;
	prog->img.addr = NULL;
	prog->map = NULL;
	return (prog);
}

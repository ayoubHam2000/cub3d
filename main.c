/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:38:46 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/28 14:12:06 by aben-ham         ###   ########.fr       */
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
	return (prog);
}

void	*init_mlx(t_prog *prog)
{
	prog->mlx = mlx_init();
	prog->win = mlx_new_window(prog->mlx, prog->w_size, prog->w_size, WIN_TITLE);
	if (!prog->mlx || !prog->win)
		return (NULL);
	return (prog);
}

int	main()
{
	t_prog	*prog;

	prog = init_prog();
	if (!prog)
		return (1);
	if (!init_mlx(prog))
		return (1);
	mlx_loop(prog->mlx);
	return (0);
}

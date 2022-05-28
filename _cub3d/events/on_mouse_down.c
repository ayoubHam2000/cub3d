/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_mouse_down.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:52:46 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/27 14:17:34 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_mouse_down(int button, int x, int y, t_prog *prog)
{
	if (button == 1)
		prog->pressed_key[3] = button;
	return (0);
}

int	on_mouse_up(int button, int x, int y, t_prog *prog)
{
	if (button == 1)
		prog->pressed_key[3] = -1;
	return (0);
}

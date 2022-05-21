/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:52:38 by aben-ham          #+#    #+#             */
/*   Updated: 2022/05/20 11:46:23 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_mouse_move(int x, int y, t_prog *prog)
{
	//if (x < 1000 && x > 0 && y > 0 && y < HEIGHT)
	//{
		prog->old_m_x = prog->m_x;
		prog->m_x = x;
	//}
	//if (y > 0 && y < HEIGHT)
	//{
		prog->old_m_y = y;
		//prog->m_y = y;
	//}
	return (0);
}
